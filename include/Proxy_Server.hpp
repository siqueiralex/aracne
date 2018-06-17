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

#include "../include/HTTP_Parser.hpp"


#define PORT 8228

class Proxy_Server{

public:

	void init();
	void get_client_request(char*);
	void reply_client(char*);
	void make_request( char*, char*);


};


#endif