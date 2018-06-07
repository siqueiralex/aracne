SOURCES_1 =  #sources .cpp
SOURCES = $(SOURCES_1)

ARACNE: 
	@ g++ -Wall -o aracne $(SOURCES) -I. 
