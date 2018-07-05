#ifndef HTML_PRS_H
#define HTML_PRS_H

#include <regex>
#include <iostream>
#include <string>
#include <string.h>
#include <list>
#include <set>

class HTML_Parser{

public:
	static std::string get_uri(std::string);
	static std::string get_host(std::string);
	static std::set<std::string> get_hrefs(const char*);
	static std::string isolate_html(const char*);

};


#endif