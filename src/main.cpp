#include <iostream>
#include "../include/HTTP_Parser.hpp"
#include "../include/Proxy_Server.hpp"

using namespace std;

int string_to_file(std::string str, const char *file){
	//save to  file
	FILE *f;
	f = fopen(file, "w");
	fprintf(f, "%s",str.c_str());
   	fclose(f);

	return 0;
}

std::string string_from_file(const char*file){

	FILE *f;
	char buffer[64768];
	f = fopen(file, "rb");
   	fread (buffer, 1, sizeof(buffer), f);
  	fclose(f);

  	std::string res(buffer);
	return res;
}

int main(){
	using namespace std;

	Proxy_Server proxy;
	proxy.init();


	string request = proxy.get_client_request();
	string_to_file(request, "request.txt");
	
   	printf("Saved the request to 'request.txt'\n");
	do{cout << '\n' << "Alter the file and press any key to make the request...";}while(cin.get() != '\n');
	
	request = string_from_file("request.txt");

   	cout << "Request: " <<  request << endl;
   	cout << "Host: " << HTTP_Parser::get_host(request) << endl;
   	cout << "Uri: " << HTTP_Parser::get_uri(request) << endl;


 
	string reply = proxy.make_request(request);
   	cout << "Reply lenght: " << reply.length() << endl;
   	cout << "Reply: " << reply << endl;
   	proxy.reply_client(reply);

   	string_to_file(reply, "reply.txt");


    //read from file
 //    char buffer[64768];
 //    f_req = fopen("request.txt", "rb");
 //    fread (buffer, 1, sizeof(buffer), f_req);
 //   	fclose(f_req);
 //   	request.assign(buffer);

 // 	std::cout<<"request saved in file: "<< request << std::endl;

	// string reply = proxy.make_request(request);

	// //remove("request.txt");

	// std::cout << "Reply: "<< reply << std::endl;


	


	// // read from file
	// 


	// 

	// do{cout << '\n' << "Press a key to close the connection...";}while(cin.get() != '\n');

	// //remove("reply.txt");


	return 0;
}






int main3(){

	using namespace std;

	FILE *f_rep;
	char reply[64768];
	f_rep = fopen("reply.txt", "rb");
    fread (reply, 1, sizeof(reply), f_rep);
   	fclose(f_rep);


   	set<string> hrefs = HTTP_Parser::get_hrefs(reply);

   for(string href: hrefs){
   		cout << href << endl;
   	}

	return 0;
}

int main1(){

	using namespace std;

	string address;

	cout << "Enter the adress you want to Spider: ";
	cin >> address;

	Proxy_Server proxy;
	proxy.init();


	return 0;
}