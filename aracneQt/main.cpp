#include <iostream>
#include "HTML_Parser.hpp"
#include "Spider.hpp"
#include "Proxy_Server.hpp"
#include "HTTP_Request.hpp"
#include "HTTP_Response.hpp"
#include "String_Functions.hpp"
#include "mainwindow.h"
#include <QApplication>

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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int port = process_arguments(argc, argv);
    cout <<"Aracne started using port: "<< port << endl;

    // Client Proxy usage
    Proxy_Server proxy = Proxy_Server(port);
    string req = proxy.get_client_request();
    HTTP_Request request = HTTP_Request(req);
    String_Functions::string_to_file(req,"./", "request.txt");

    string reply = proxy.make_request(request.Assembly_Request());
    HTTP_Response response = HTTP_Response(reply);
    String_Functions::string_to_file(reply,"./", "response.txt");
    proxy.reply_client(response.Assembly_Response());



    // string url("www.ba.gov.br");
    // Spider spider = Spider(url, port);
    // spider.dump_htmls(0);

    //do the same changing the final line to:
    //spider.generate_tree(level);
    //to simply generate the tree.

    return a.exec();
}
