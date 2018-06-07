SOURCES_1 = 
#sources da gerencia de arquivos
SOURCES = $(SOURCES_1)

ARACNE: 
	@ g++ -Wall -o aracne $(SOURCES) -I. 
