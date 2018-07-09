#ifndef PROX_SRV_H
#define PROX_SRV_H
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "../include/HTTP_Request.hpp"
#include "../include/HTTP_Response.hpp"


#define PORT 8228

class Proxy_Server{

public:
	Proxy_Server(int);
	HTTP_Request get_client_request();
	void reply_client(HTTP_Response);
	HTTP_Response make_request(HTTP_Request);

	int server_socket, outbound_socket;
	struct sockaddr_in serv_addr;
	int addrlen, valread;
	int opt;
	char buffer[64768];

};


#endif