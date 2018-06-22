#include <iostream>
#include "../include/HTTP_Parser.hpp"
#include "../include/Proxy_Server.hpp"
#include "../include/HTTP_Request.hpp"
#include "../include/HTTP_Response.hpp"
#include "../include/String_Functions.hpp"

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

	string Req_raw = string_from_file("request.txt");

	HTTP_Request Request(Req_raw);

	cout << "Method: " << Request.method<<endl;
	cout << "URL: " << Request.url << endl;
	cout << "Version: " << Request.version<< endl;

	for(std::map<string, string>::iterator it=Request.fields.begin(); it!=Request.fields.end(); ++it){
		cout << it->first << ": " << it->second << endl;
	}

	cout<<"body: " << Request.body<<endl;


	return 0;
}
