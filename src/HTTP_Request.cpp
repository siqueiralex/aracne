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

    //lacks the body parser

};
HTTP_Request::HTTP_Request(){

    method = "GET";
    version = "HTTP/1.1";
    url = "";
    body = "";

};

std::string HTTP_Request::assembly(){
    using namespace std;
    string Request("");

    Request.append(method);
    Request.append(" ");
    Request.append(url);
    Request.append(" ");
    Request.append(version);
    Request.append("\r\n");

    for (std::map<string,string>::iterator it=fields.begin(); it!=fields.end(); ++it){
        Request.append(it->first);
        Request.append(" ");
        Request.append(it->second);
        Request.append("\r\n");
    }
    Request.append("\r\n");
    Request.append(body);

    return Request;

}

void HTTP_Request::print(){
    cout << "method: " << method << endl;
    cout << "version: " << version << endl;
    cout << "url: " << url << endl;

    for(map<string, string>::iterator it = fields.begin(); it!=fields.end(); ++it){
        cout << it->first << " " << it->second << endl;
    }
    cout << "body: " << body << endl<<endl;

    cout << "Assembled: " << endl << assembly() << endl;
}

void HTTP_Request::treat(){
    //version = "HTTP/1.0";
    fields["Connection:"] = "close";
    fields["Accept-Encoding:"] = "identity";

}

bool HTTP_Request::eval(){
    if( method != "GET") return false;
    return true;
}