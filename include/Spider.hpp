#ifndef SPIDER_H
#define SPIDER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <string.h>

class Spider{

public:

	Spider(std::string, int);
	int proxy_port;
	bool valid;
	std::string root;
	std::string host;
	std::set<std::string> visited_urls;
	std::map<std::string, std::string> htmls;
	std::map<std::string, std::string> dictionary;
	std::map<std::string, std::string> aliases;
	std::map<std::string, std::set<std::string>> par_child;
	bool eval_url(std::string url);
	std::string parse_url(std::string url);
	std::string url_to_filename(std::string url);
	void generate_tree(int);
	void print_tree(int);
	void dump(int);

};


#endif