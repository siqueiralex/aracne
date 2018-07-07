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


#define PORT 8228

class Proxy_Server{

public:
	Proxy_Server(int);
	std::string get_client_request();
	void reply_client(std::string);
	std::string make_request(std::string);


};


#endif