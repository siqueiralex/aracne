#include "../include/Proxy_Server.hpp"
#include "../include/String_Functions.hpp"

using namespace std;

Proxy_Server::Proxy_Server(int port){

    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0){
        std::cout << "Erro ao criar socket" << std::endl;
        exit(-1);
    }

    int opt = 1;
    if(setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cout << "Erro ao setar opcaos do socket" << std::endl;
        exit(-1);
    }

    // Faz o bind do socket com a porta
    if(bind(server_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "Falha no bind!" << std::endl;
        exit(-1);
    }

    // Comeca a ouvir a porta
    if(listen(server_socket, 100) < 0) {
        std::cout << "Erro na socket_server ao ouvir a porta " << port << std::endl;
        exit(-1);
    }    


};

string parse_url(string url){
    string parsed("");
    string internal = url;
    vector<string> result = String_Functions::split(internal, "//");
    if(result.size()==2)        
        internal = result[1];
        
    if(internal.find('/')!=0){
        vector<string> result2 = String_Functions::split_on_first(internal, "/");
        parsed = "/";
        parsed.append(result2[1]);
    }else{
        parsed = url;
    }       
    
    return parsed;
}

void treat_request(HTTP_Request *request){
    request->url = parse_url(request->url);
    request->fields["Accept-Encoding:"] = "identity";
    request->fields["Connection:"] = "close";
}

bool evaluate_request(HTTP_Request request){

    if(request.method != "GET") return false;

    return true;
}


HTTP_Request Proxy_Server::get_client_request(){
    
    char buffer[64768];
    struct sockaddr cli_addr;
    socklen_t clilen = sizeof(cli_addr);

    int sock = accept(server_socket, &cli_addr, (socklen_t*) &clilen);

    if(read(sock, buffer, sizeof(buffer))<0){
        cout << "Falha ao tentar ler requisição do navegador" << endl;
        exit(-1);
    }
    std::string request_text(buffer);

    HTTP_Request request = HTTP_Request(request_text);
    treat_request(&request);
    if(evaluate_request(request)){
        request.client_socket = sock;
        request.accepted = true;
    }
    else{
        request.accepted = false;
        close(request.client_socket);
        request.client_socket = -1;
    }

    return request;
}


HTTP_Response Proxy_Server::make_request(HTTP_Request request){

    if(!request.accepted){
        HTTP_Response response = HTTP_Response();
        response.client_socket = request.client_socket;
        return response;
    }

    string host = request.fields["Host:"];

    struct addrinfo hints;
    struct addrinfo *resp;
    bzero((char *) &hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if(getaddrinfo(host.c_str(), "80", &hints, &resp) != 0){
        std::cout << "Erro ao resolver host: " << host << std::endl;
        exit(1);
    }

    outbound_socket = socket(resp->ai_family, resp->ai_socktype, resp->ai_protocol);
    if(outbound_socket < 0){
        std::cout << "Erro ao criar socket para requisicao" << std::endl;
        exit(-1);
    }

    if(connect(outbound_socket, resp->ai_addr, resp->ai_addrlen) < 0){
        std::cout << "Erro ao conectar ao host: " << host << std::endl;
        exit(-1);
    }

    string request_text = request.Assembly_Request();

    if(send(outbound_socket, request_text.c_str(), request_text.length(), 0)<0){
        cout << "Erro ao conectar ao enviar request: " << endl;
        exit(-1);
    }    
    
    char buff[1];
    string reply("");
    valread = read(outbound_socket, &buff, sizeof(buff));  
    while(valread>0){
        reply.append(buff);
        valread = read(outbound_socket, &buff, sizeof(buff));
    }
    if(valread<0){
        cout<< "ERRO LENDO RESPOSTA DO SERVIDOR!" <<endl;
    }

    HTTP_Response response = HTTP_Response(reply);
    response.client_socket = request.client_socket;

    close(outbound_socket); 

    return response;

}

void Proxy_Server::reply_client(HTTP_Response response){

    int sock = response.client_socket;
    if(sock>0){    
        string reply = response.Assembly_Response();
        if(send(sock, reply.c_str(), reply.size(), 0)<0){
            perror("failed to send reply");
            exit(EXIT_FAILURE);
        }
        close(sock);
    }    
}
