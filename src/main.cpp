#include <iostream>
#include "../include/HTML_Parser.hpp"
#include "../include/Proxy_Server.hpp"
#include "../include/HTTP_Request.hpp"
#include "../include/HTTP_Response.hpp"
#include "../include/String_Functions.hpp"

using namespace std;

int main(){

	using namespace std;

	string teste("AHH  TESTE\r\nTESTE2\n");

	String_Functions::string_to_file( teste , "teste.txt");

}
