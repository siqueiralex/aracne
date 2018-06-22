#include "../include/HTTP_Response.hpp"
#include "../include/String_Functions.hpp"

using namespace std;
//construtor


HTTP_Response::HTTP_Response(std::string Response_String){

    
    vector<string> splitted = String_Functions::split(Response_String, "\r\n\r\n");
    string header = splitted[0];
	data = splitted[1];

	vector<string> hd_lines = String_Functions::split(header, "\r\n");
	string first_line = hd_lines[0];
	vector<string> fl_tokens = String_Functions::split_on_first(first_line, " ");
    version = fl_tokens[0];
    status_code = fl_tokens[1];

    vector<string> temp;
    for( int i = 1; i<hd_lines.size(); i++){
         temp = String_Functions::split_on_first(hd_lines[i], " ");
         fields[temp[0]] = temp[1];
    }

};
