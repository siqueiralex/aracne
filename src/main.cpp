#include <iostream>
#include "../include/HTML_Parser.hpp"
#include "../include/Spider.hpp"
#include "../include/Proxy_Server.hpp"
#include "../include/HTTP_Request.hpp"
#include "../include/HTTP_Response.hpp"
#include "../include/String_Functions.hpp"

using namespace std;

int port;

void process_arguments(int argc, char **argv){
	port = 8228;
	if(argc==2){
		string arg(argv[1]);
		if(arg.find("-p")==0){ 
			arg = arg.substr(2,arg.length());
		 	if(atoi(arg.c_str())>0 && atoi(arg.c_str()) <100000)
				port = atoi(arg.c_str());
		}
	}
	if(argc==3){
		string arg(argv[1]);
		if(arg=="-p")	
			if(atoi(argv[2])>0 && atoi(argv[2])<100000)
				port = atoi(argv[2]);
	}
}

void traffic_inspector(Proxy_Server *proxy){
	cout << "Traffic inspector is listening on port " << port << endl;
	while(1){
		string req = proxy->get_client_request();
		HTTP_Request request = HTTP_Request(req);
		cout << "Request received - Host: " << request.fields["Host:"] << " URL: " << request.url << endl; 
		if(request.eval()){
			String_Functions::string_to_file(req, ".", "request.txt");
			system("nano request.txt");
			req = String_Functions::string_from_file("request.txt");
			string reply = proxy->make_request(req);
			HTTP_Response response = HTTP_Response(reply);
			String_Functions::string_to_file(reply, ".", "response.txt");
			system("nano response.txt");
			reply = String_Functions::string_from_file("response.txt");
			proxy->reply_client(reply);
		}else{
			cout <<endl<< "Rejected! Only GET/HTTP requests accepted! " << endl;
			request.print(); cout << endl<<endl;
		}
	}
}

int print_main_menu(){
	string option;
	cout << "(1) Traffic Inspector" << endl;
	cout << "(2) Generate Tree of Url's" << endl;
	cout << "(3) Dump website" << endl;
	cout << "(4) Exit" << endl;
	cout << "Select your option ->> ";
	cin >> option;
	return atoi(option.c_str());
}

void gen_tree(){

}

void dump(){

}

int main(int argc, char **argv){

	process_arguments(argc, argv);
	cout <<"Aracne started using port: "<< port << endl;
	
	int opt = 1;
	while(opt!=4){
		opt = print_main_menu();	
		if(opt>0 && opt <5){
			if(opt==1){
				Proxy_Server proxy = Proxy_Server(port); 
				traffic_inspector(&proxy);
			}
			if(opt==2) gen_tree();
			if(opt==3) dump();
		}
		system("clear");
		if(opt <1 || opt >4) cout << "Opção inválida!" << endl;
	}


	

	return 0;
}

