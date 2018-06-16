#include "../include/HTTP_Parser.hpp"

// any global variable



char* HTTP_Parser::get_uri(char* header, char* uri){
	using namespace std;

	string str(header);
    regex r("GET\\s*([^ ]*)");
    smatch m;
    regex_search(str, m, r);
    string temp = m[1];
    strcpy(uri, temp.c_str());

	return 0;

}