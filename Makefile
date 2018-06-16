all: aracne

HTTP_Parser.o:
	g++ -g -c -std=c++11 src/HTTP_Parser.cpp

Proxy_Server.o:
	g++ -g -c src/Proxy_Server.cpp

aracne: HTTP_Parser.o Proxy_Server.o src/main.cpp
	g++ -Wall -std=c++11 -o aracne HTTP_Parser.o Proxy_Server.o src/main.cpp

clean: 
	rm HTTP_Parser.o Proxy_Server.o
