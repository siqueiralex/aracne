#include <iostream>
#include "../include/HTTP_Parser.hpp"
#include "../include/Proxy_Server.hpp"

using namespace std;


int main(){

	FILE *f_req, *f_rep;

	Proxy_Server proxy;
	proxy.init();

	char request[4096];

	proxy.get_client_request(request);

	//save to  file
	f_req = fopen("request.txt", "w");
	fprintf(f_req, "%s",request);
   	fclose(f_req);

   	printf("Saved the incoming request to 'request.txt'\n");
    do{cout << '\n' << "Alter the file and press any key to make the request...";}while(cin.get() != '\n');


    //read from file
    f_req = fopen("request.txt", "rb");
    fread (request, 1, sizeof(request), f_req);
   	fclose(f_req);


	char reply[8192];
	proxy.make_request( request, reply);

	remove("request.txt");

	// save to file
	f_rep = fopen("reply.txt", "w");
	fprintf(f_rep, "%s",reply);
   	fclose(f_rep);

   	printf("Saved the resulting reply to 'reply.txt'\n");
	do{cout << '\n' << "Alter the file and press any key to send back the reply...";}while(cin.get() != '\n');

	// read from file
	f_rep = fopen("reply.txt", "rb");
    fread (reply, 1, sizeof(reply), f_rep);
   	fclose(f_rep);


	proxy.reply_client(reply);

	do{cout << '\n' << "Press a key to close the connection...";}while(cin.get() != '\n');

	remove("reply.txt");


	return 0;
}