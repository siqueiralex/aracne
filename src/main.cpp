#include <iostream>
#include "../include/HTTP_Parser.hpp"
#include "../include/Proxy_Server.hpp"
#include "../include/HTTP_Request.hpp"
#include "../include/HTTP_Response.hpp"

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

	string Res_raw = string_from_file("reply.txt");

	HTTP_Response Response(Res_raw);

	cout << "Data: " << Response.data << endl;


	
	return 0;
}
