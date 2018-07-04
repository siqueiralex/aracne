#include <iostream>
#include "../include/HTML_Parser.hpp"
#include "../include/Spider.hpp"
#include "../include/Proxy_Server.hpp"
#include "../include/HTTP_Request.hpp"
#include "../include/HTTP_Response.hpp"
#include "../include/String_Functions.hpp"

using namespace std;

int main(){

	using namespace std;
	string url("http://www.ba.gov.br/");
	Spider spider = Spider(url);
	spider.dump_htmls(1);
	

}

