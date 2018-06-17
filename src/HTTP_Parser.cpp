#include "../include/HTTP_Parser.hpp"

// any global variable



char* HTTP_Parser::get_uri(char* request, char* uri){
	using namespace std;

	string str(request);
    regex r("GET \\s*([^ ]*)");
    smatch m;
    regex_search(str, m, r);
    string temp = m[1];
    strcpy(uri, temp.c_str());

	return 0;

}

char* HTTP_Parser::get_host(char* request, char* host){
	using namespace std;

	string str(request);
    regex r("Host: \\s*([^\\r]*)");
    smatch m;
    regex_search(str, m, r);
    string temp = m[1];
    strcpy(host, temp.c_str());

	return 0;

}