#ifndef SPIDER_H
#define SPIDER_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <string.h>

class Spider{

public:

	Spider();
	std::string host;
	std::vector<std::string> visited_urls;
	bool eval_url(std::string url);

};


#endif