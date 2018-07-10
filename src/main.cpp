/*
	Classe principal que implementa a Command Line Interface, que printa menus e define a excução do Aracne

*/

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

int print_traffic_menu(){
	string option;
	cout << "(1) Inspect another Request/Reply" << endl;
	cout << "(Any other) Back to main menu" << endl;
	cout << "Your option -->> ";
	cin >> option;
	return atoi(option.c_str());
}

void traffic_inspector(){
	int opt = 1;
	Proxy_Server proxy = Proxy_Server();
	proxy.init(port);
	system("clear");
	cout << "Traffic inspector is listening on port " << port << endl;
	cout << "Waiting for Request..." << endl;	
	while(opt == 1){
		system("clear");
		cout << "Traffic inspector is listening on port " << port << endl;
		cout << "Waiting for Request..." << endl;
		string req = proxy.get_client_request();
		HTTP_Request request = HTTP_Request(req);
		cout << "Request received - Host: " << request.fields["Host:"] << " URL: " << request.url << endl; 
		if(request.eval()){
			String_Functions::string_to_file(req, ".", "request.txt");
			system("nano request.txt");
			req = String_Functions::string_from_file("request.txt");
			// do{cout << '\n' << "Press any key to send the request";}while (cin.get() != '\n');
			// cout << "Waiting for Response..." << endl;
			string reply = proxy.make_request(req);
			HTTP_Response response = HTTP_Response(reply);
			String_Functions::string_to_file(reply, ".", "response.txt");
			system("nano response.txt");
			reply = String_Functions::string_from_file("response.txt");
			//do{cout << '\n' << "Press any key to send the reply";}while (cin.get() != '\n');
			proxy.reply_client(reply);
			system("clear");
			//opt = print_traffic_menu();
			cout << "Traffic inspector is listening on port " << port << endl;
			cout << "Waiting for Request..." << endl;
		}else{
			cout <<endl<< "Rejected! Only GET/HTTP requests accepted! " << endl;
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
	string url;
	system("clear");
	cout << "Generate Tree" << endl;
	cout << "Type the url you want to inspect: ";
	cin >> url;
	Spider spider = Spider(url);

	while(!spider.valid){
		system("clear");
		cout << "You have typed an invalid url!" << endl;
		cout << "Generate Tree" << endl;
		cout << "Type the url you want to inspect: ";
		cin >> url;
		spider = Spider(url);
	}
	int lev=0;
	while(lev<1 || lev>4){
		system("clear");
		string levels;
		cout << "Type the number of levels you want to inspect [1 < L < 4]= " ;
		cin >> levels;
		lev = atoi(levels.c_str());
	}
	spider.generate_tree(lev-1);
	spider.print_tree(lev-1);
	string temp;
	cout << "Press any key to go back to main menu...";
	cin >> temp;
}


void dump(){
	
	string url;
	system("clear");
	cout << "Dump website" << endl;
	cout << "Type the url you want to dump: ";
	cin >> url;
	Spider spider = Spider(url);

	while(!spider.valid){
		system("clear");
		cout << "You have typed an invalid url!" << endl;
		cout << "Dump website" << endl;
		cout << "Type the url you want to dump= ";
		cin >> url;
		spider = Spider(url);
	}
	int lev=0;
	while(lev<1 || lev>2){
		system("clear");
		string levels;
		cout << "Type the number of levels you want to inspect [1 or 2]= " ;
		cin >> levels;
		lev = atoi(levels.c_str());
	}
	spider.dump(lev-1);

	string temp;
	cout << "Press any key to go back to main menu...";
	cin >> temp;

}

int main(int argc, char **argv){

	process_arguments(argc, argv);
	cout <<"Aracne started using port: "<< port << endl;
	
	int opt = 1;
	while(opt!=4){
		system("clear");
		if(opt <1 || opt >4) cout << "Opção inválida!" << endl;
		opt = print_main_menu();	
		if(opt>0 && opt <5){
			if(opt==1){ 
				traffic_inspector();
			}
			if(opt==2) gen_tree();
			if(opt==3) dump();
		}
	}


	

	return 0;
}

