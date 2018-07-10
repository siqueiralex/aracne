#include <iostream>
#include "HTML_Parser.hpp"
#include "Spider.hpp"
#include "Proxy_Server.hpp"
#include "HTTP_Request.hpp"
#include "HTTP_Response.hpp"
#include "String_Functions.hpp"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();


//    int port = process_arguments(argc, argv);
//    cout <<"Aracne started using port: "<< port << endl;

//     Client Proxy usage
//    Proxy_Server proxy = Proxy_Server(port);
//    string req = proxy.get_client_request();
//    HTTP_Request request = HTTP_Request(req);
//    String_Functions::string_to_file(req,"./", "request.txt");

//    string reply = proxy.make_request(request.Assembly_Request());
//    HTTP_Response response = HTTP_Response(reply);
//    String_Functions::string_to_file(reply,"./", "response.txt");
//    proxy.reply_client(response.Assembly_Response());


//     string url("www.ba.gov.br");
//     Spider spider = Spider(url, port);
//     spider.dump_htmls(0);

//    do the same changing the final line to:
//    spider.generate_tree(level);
//    to simply generate the tree.

}