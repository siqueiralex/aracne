#ifndef HTTP_PRS_H
#define HTTP_PRS_H

#include <regex>
#include <iostream>
#include <string>
#include <string.h>

class HTTP_Parser{

public:

	static char* get_uri(char*, char*);
	static char* get_host(char*, char*);
};


#endif