#include <iostream>
#include "../include/HTTP_Parser.hpp"
#include "../include/Proxy_Server.hpp"

using namespace std;


int main(){

	Proxy_Server proxy;
	
	proxy.init();

	char request[4096];

	proxy.get_client_request(request);
	
	printf("REQUEST: %s\n\n", request);

	char uri[256];
	HTTP_Parser::get_uri(request, uri);

	printf("URI: %s\n", uri );
	
	do{

	   cout << '\n' << "Press a key to make request...";
	
	}while(cin.get() != '\n');

	char reply[8192];
	proxy.make_request(uri, reply);

	printf("REPLY: %s\n\n", reply);

	do{

	   cout << '\n' << "Press a key to send the reply...";
	
	}while(cin.get() != '\n');


	proxy.reply_client(reply);

	do{

	cout << '\n' << "Press a key to close the connection...";
	
	}while(cin.get() != '\n');



	return 0;
}