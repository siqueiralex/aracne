#include "../include/Proxy_Server.hpp"

int server_fd, client_socket, outbound_socket;
struct sockaddr_in address;
int addrlen, valread;
int opt;
char buffer[64768];

Proxy_Server::Proxy_Server(int port){
	addrlen = sizeof(address);
	opt = 1;
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 5) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

};

std::string Proxy_Server::get_client_request(){
    
    char buffer[64768];

    if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    read(client_socket , buffer, sizeof(buffer));

    std::string request(buffer);
    return request;
}



std::string Proxy_Server::make_request(std::string req){

    using namespace std;

    struct hostent *req_host;
    struct sockaddr_in serv_addr;
    string request = req;

    if((outbound_socket = socket(AF_INET,SOCK_STREAM,0)) < 0);

    HTTP_Request reqst = HTTP_Request(request);
    string host = reqst.fields["Host:"];

    req_host = gethostbyname(host.c_str());
    if ( (req_host == NULL) || (req_host->h_addr == NULL) ) {
        std::cout << "Error retrieving DNS information." << std::endl;
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(80);

    memcpy(&serv_addr.sin_addr.s_addr,req_host->h_addr,sizeof(req_host->h_addr));

    if (connect(outbound_socket,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0);
    
    send(outbound_socket, request.c_str(), request.length(), 0);
    
    char buff[1];
    valread = read(outbound_socket, &buff, sizeof(buff));
    string reply(buff); 
    valread = read(outbound_socket, &buff, sizeof(buff));  
    while(valread>0){
        reply.append(buff);
        valread = read(outbound_socket, &buff, sizeof(buff));
    }

    return reply;


}

void Proxy_Server::reply_client(std::string reply){
    if(send(client_socket, reply.c_str(), reply.length(), 0)<0){
        perror("failed to send reply");
        exit(EXIT_FAILURE);
    }
    close(client_socket);
}