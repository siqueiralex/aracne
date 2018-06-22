#include "../include/HTTP_Response.hpp"

using namespace std;
//construtor


HTTP_Response::HTTP_Response(std::string Response_String){

    std::size_t found = Response_String.find_first_of('\r');
    if (found!=std::string::npos)
        data = Response_String.substr(found, Response_String.length());

};


std::vector<std::string> HTTP_Response::split(const std::string& s, const char& c)
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
