all: aracne

HTTP_Parser.o:
	g++ -g -c -std=c++11 src/HTTP_Parser.cpp

HTTP_Request.o:
	g++ -g -c -std=c++11 src/HTTP_Request.cpp

HTTP_Response.o:
	g++ -g -c -std=c++11 src/HTTP_Response.cpp

Proxy_Server.o: 
	g++ -g -c -std=c++11 src/Proxy_Server.cpp 

aracne: HTTP_Parser.o Proxy_Server.o HTTP_Response.o HTTP_Request.o src/main.cpp
	g++ -Wall -std=c++11 -o aracne HTTP_Parser.o HTTP_Request.o HTTP_Response.o Proxy_Server.o src/main.cpp

clean: 
	rm HTTP_Parser.o Proxy_Server.o HTTP_Request.o aracne
