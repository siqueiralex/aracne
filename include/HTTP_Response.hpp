#ifndef HTTP_RESP_H
#define HTTP_RESP_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <string.h>

class HTTP_Response{

public:

	HTTP_Response(std::string);

	std::string status_code;
	std::string version;
	std::map<std::string, std::string> fields; 
	std::string data;



	static std::vector<std::string> split(const std::string& s, const char& c);


};


#endif