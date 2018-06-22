#include "../include/String_Functions.hpp"

using namespace std;

std::vector<std::string> String_Functions::split(std::string str, const char * delimiter){

    vector<string> tokens;

    std::size_t last_found = -1;
    std::size_t found =str.find(delimiter, last_found+1);
    while(found<str.length()){
        tokens.push_back(str.substr(last_found+1, found - last_found -1));
        last_found = found;
        found = str.find(delimiter, last_found+1);
    }

    return tokens;
}
