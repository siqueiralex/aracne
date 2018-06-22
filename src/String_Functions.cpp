#include "../include/String_Functions.hpp"

using namespace std;

std::vector<std::string> String_Functions::split(std::string str, const char * delimiter){

    vector<string> tokens;
    string os(delimiter);
    int offset = os.length();

    std::size_t last_found = -1*offset;
    std::size_t found =str.find(delimiter, last_found+offset);
    while(found<str.length()){
        tokens.push_back(str.substr(last_found+offset, found - last_found -offset));
        last_found = found;
        found = str.find(delimiter, last_found+offset);
    }
    if((last_found+offset)<str.length())
        tokens.push_back(str.substr(last_found+offset, str.length()));

    return tokens;
}

std::vector<std::string> String_Functions::split_on_first(std::string str, const char * delimiter){

    vector<string> tokens;
    string os(delimiter);
    int offset = os.length();

    std::size_t found =str.find(delimiter);
    tokens.push_back(str.substr(0, found));
    tokens.push_back(str.substr(found+offset, str.length()-offset));

    return tokens;
}