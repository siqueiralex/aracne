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
    if (listen(server_fd, 3) < 0)
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

void Proxy_Server::make_request(char* uri, char* reply){

    if ((outbound_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }


    struct sockaddr_in remote_address;
    remote_address.sin_family = AF_INET;
    remote_address.sin_port = htons(80);
    
    inet_aton(uri, (struct in_addr *) &remote_address.sin_addr.s_addr);



    if(connect(outbound_socket, (struct sockaddr *)  &remote_address, sizeof(remote_address))<0){
        perror("connection failed");
        exit(EXIT_FAILURE);
    }
    

    char request[] = "GET / HTTP/1.1\r\n\r\n";

    if(send(outbound_socket, request, sizeof(request), 0)<0){
        perror("failed to send request");
        exit(EXIT_FAILURE);
    }

    if(recv(outbound_socket, &buffer, sizeof(buffer), 0)<0){
        perror("failed to receive reply");
        exit(EXIT_FAILURE);
    }

    strcpy(reply, buffer);

    close(outbound_socket);
}

void Proxy_Server::reply_client(char* reply){
    strcpy(buffer, reply);
    if(send(client_socket, buffer, sizeof(buffer), 0)<0){
        perror("failed to send reply");
        exit(EXIT_FAILURE);
    }
    close(client_socket);
}