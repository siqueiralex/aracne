#include "../include/HTTP_Request.hpp"
#include "../include/String_Functions.hpp"

using namespace std;
//construtor


HTTP_Request::HTTP_Request(std::string Request_String){

    vector<string> splitted = String_Functions::split(Request_String, "\r\n\r\n");
    string header = splitted[0];
    if(splitted.size()>1)body = splitted[1];

    vector<string> lines = String_Functions::split(header, "\r\n");

    //parsing header
    string first_line = lines[0];
    vector<string> fl_tokens = String_Functions::split(first_line, " ");
    method = fl_tokens[0];
    url = fl_tokens[1];
    version = fl_tokens[2];

    vector<string> temp;
    for( int i = 1; i<lines.size(); i++){
         temp = String_Functions::split_on_first(lines[i], " ");
         fields[temp[0]] = temp[1];
    }

};
