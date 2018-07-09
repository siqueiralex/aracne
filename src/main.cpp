#include <iostream>
#include <thread>  
#include "../include/HTML_Parser.hpp"
#include "../include/Spider.hpp"
#include "../include/Proxy_Server.hpp"
#include "../include/HTTP_Request.hpp"
#include "../include/HTTP_Response.hpp"
#include "../include/String_Functions.hpp"

using namespace std;

int process_arguments(int argc, char **argv){
	int port = 8228;
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
	
	return port;
}

// void bypass(Proxy_Server *p){
// 	string req;
// 	string reply;
// 	Proxy_Server proxy = (*p);
// 	cout << "initiated thread" << endl;
// 	while(1){
		
// 		try {
// 		    req = proxy.get_client_request();
// 			HTTP_Request request = HTTP_Request(req);
// 			cout << "Requested: "<< request.url << endl;
// 			reply = proxy.make_request(req);
// 			proxy.reply_client(reply);
// 		}
// 		catch (...) {
// 		    cout<<"Couldnt resolve..."<< endl;

// 		}
// 	}

// }


// int main(int argc, char **argv){

// 	int port = process_arguments(argc, argv);
// 	cout <<"Aracne started using port: "<< port << endl;
	
// 	Proxy_Server proxy = Proxy_Server(port);
	
// 	thread first (bypass, &proxy);
//   	thread second (bypass, &proxy); 
//   	thread third (bypass, &proxy);
//   	thread fourth (bypass, &proxy); 
//   	thread fifth (bypass, &proxy);
//   	thread sixth (bypass, &proxy); 



//   	first.join();                
// 	second.join(); 
// 	third.join();                
// 	fourth.join(); 
// 	fifth.join();
// 	sixth.join();



// 	return 0;
// }

int main(int argc, char **argv){

	int port = process_arguments(argc, argv);
	cout <<"Aracne started using port: "<< port << endl;
	Proxy_Server proxy = Proxy_Server(port);
	while(1){
		HTTP_Request request = proxy.get_client_request();
		cout << "Received incoming request for: " << request.url << " ";
		if(request.accepted){
			cout << "Passed!" << endl;
			String_Functions::string_to_file(request.Assembly_Request(), "./", "request.txt");
			HTTP_Response response = proxy.make_request(request);
			String_Functions::string_to_file(response.Assembly_Response(), "./", "response.txt");
			proxy.reply_client(response);
		}else
			cout << "Denied " << endl;
	}




	return 0;
}


// int main(){

// 	string host("http://wwwasda");



// 	vector<string> splitted = String_Functions::split(host, ":");

// 	cout << atoi(splitted[1].c_str()) << endl;

// }