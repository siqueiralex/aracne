#include "../include/HTTP_Request.hpp"

using namespace std;
//construtor


HTTP_Request::HTTP_Request(std::string Request_String){

    //parsing header
    vector<string> lines = HTTP_Request::split(Request_String.c_str(), '\n');
    string first_line = lines[0];
    vector<string> fl_tokens = HTTP_Request::split(first_line.c_str(), ' ');
    method = fl_tokens[0];
    url = fl_tokens[1];
    version = fl_tokens[2];


    // parsing fields
    string line;
    string buff;
    int found;
    for( int i = 1; i<lines.size(); i++){
         line = lines[i];
         buff="";
         found = 1;
         for(auto n:line){
            if(n!=' ' && found==1) 
                buff+=n;
            else if(n==' ' && found ==1) {
                found = 0;
                fields[buff]="";
            }    
            else{
            fields[buff]+=n;
            }
         }

    }

};


std::vector<std::string> HTTP_Request::split(const std::string& s, const char& c)
{
    using namespace std;
    string buff{""};
    vector<string> v;
    
    for(auto n:s)
    {
        if(n != c) buff+=n; else
        if(n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if(buff != "") v.push_back(buff);
    
    return v;
}
