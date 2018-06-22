#ifndef HTTP_REQ_H
#define HTTP_REQ_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <string.h>

class HTTP_Request{

public:

	HTTP_Request(std::string);

	std::string method;
	std::string url;
	std::string version;
	std::map<std::string, std::string> fields; 




	static std::vector<std::string> split(const std::string& s, const char& c);


};


#endif