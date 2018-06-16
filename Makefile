all: aracne

HTTP_Parser.o: src/HTTP_Parser.cpp
	g++ -g -c -std=c++11 src/HTTP_Parser.cpp

aracne: HTTP_Parser.o src/main.cpp
	g++ -Wall -std=c++11 -o aracne HTTP_Parser.o src/main.cpp

clean: 
	rm HTTP_Parser.o 