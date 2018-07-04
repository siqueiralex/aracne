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
	string reply = String_Functions::string_from_file("reply.txt");
	Spider spider = Spider();
	spider.host = "www.ba.gov.br";


	set<string> hrefs;
	hrefs.insert("/");
	hrefs.insert("//cdn.jsdelivr.net/bootstrap/3.3.7/css/bootstrap.css");
	hrefs.insert("/cidadao");
	hrefs.insert("http://creativecommons.org/licenses/by-nd/3.0/br/");
	hrefs.insert("http://dovirtual.ba.gov.br/egba/reader2/");
	hrefs.insert("https://www.ba.gov.br/");
	hrefs.insert("http://www.ba.gov.br/cidadao");
	hrefs.insert("https://issuu.com/hpitanga/docs/revista_secom_terra_mae_2017_web");

	for (set<string>::iterator it=hrefs.begin(); it!=hrefs.end(); ++it){
        cout << *it << ": ";
        if(spider.eval_url(*it))
        	cout << "TRUE" << endl;
        else
        	cout << "FALSE" << endl;
    }


	





}

