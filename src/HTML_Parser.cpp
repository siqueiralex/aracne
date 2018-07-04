#include "../include/HTML_Parser.hpp"

// any global variable



std::string HTML_Parser::get_uri(std::string request){
	using namespace std;

	string str = request;
    regex r("GET \\s*([^ ]*)");
    smatch m;
    regex_search(str, m, r);
    return m[1];
    

}

std::string HTML_Parser::get_host(std::string request){
	using namespace std;

	string str = request;
    regex r("Host: \\s*([^\\r]*)");
    smatch m;
    regex_search(str, m, r);
    
    return m[1];
    
}

std::set<std::string> HTML_Parser::get_hrefs(const char *body){
    using namespace std;

    string str(body);
    regex r("href=\"(.*?)\"", regex_constants::icase);
    set<string> hrefs = { sregex_token_iterator(str.begin(), str.end(), r, 1), sregex_token_iterator{} };

    return hrefs;

}