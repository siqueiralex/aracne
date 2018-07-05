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

std::string HTML_Parser::isolate_html(const char *data){
    using namespace std;
    
    string str(data);
    int from =str.find("<");
    int to = str.find("</html>");

    if(from>=str.length())
        return str;

    if(to>=str.length())
        return str.substr(from, str.length()-from);

    return str.substr(from, to-from+7);
}