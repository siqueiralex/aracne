#include "../include/Proxy_Server.hpp"

int server_fd, client_socket, outbound_socket;
struct sockaddr_in address;
int addrlen;
int opt;
char buffer[8096];

void Proxy_Server::init(){
	addrlen = sizeof(address);
	opt = 1;

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 1) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

}

void Proxy_Server::get_client_request(char* request){
    
    char buffer[4096];

    if ((client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    read( client_socket , buffer, sizeof(buffer));

    strcpy(request, buffer);
}

void Proxy_Server::make_request(char *request, char* reply){

    struct hostent *req_host;
    struct sockaddr_in serv_addr;

    if((outbound_socket = socket(AF_INET,SOCK_STREAM,0)) < 0);

    char host[256];
    HTTP_Parser::get_host(request, host);

    std::cout<<host;

    req_host = gethostbyname(host);
    if ( (req_host == NULL) || (req_host->h_addr == NULL) ) {
        std::cout << "Error retrieving DNS information." << std::endl;
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(80);

    memcpy(&serv_addr.sin_addr.s_addr,req_host->h_addr,sizeof(req_host->h_addr));

    if (connect(outbound_socket,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0);
    
    char temp[8192];
    strcpy(temp, request);

    send(outbound_socket, temp, sizeof(temp), 0);
    recv(outbound_socket, &buffer, sizeof(buffer),0);

    strcpy(reply, buffer);


}

void Proxy_Server::reply_client(char* reply){
    strcpy(buffer, reply);
    if(send(client_socket, buffer, sizeof(buffer), 0)<0){
        perror("failed to send reply");
        exit(EXIT_FAILURE);
    }
    close(client_socket);
}