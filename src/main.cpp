#include <iostream>
#include "../include/HTTP_Parser.hpp"

using namespace std;


int main(){

	char header[1024] = "GET http://twitter-data-monitor-unb.herokuapp.com/ HTTP/1.1\nHost(...)";
	char uri[256];

	HTTP_Parser::get_uri(header, uri);

	printf("%s\n", uri);


	return 0;
}