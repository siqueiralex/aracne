#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){

	char reponse_data[1024] = "HTTP/1.1 200 OK\r\n\n<html><body><h1>That's Server reply!</h1></body></html>";


	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	//define the adress
	struct sockaddr_in server_adress;
	server_adress.sin_family = AF_INET;
	server_adress.sin_port = htons(8001);
	server_adress.sin_addr.s_addr = INADDR_ANY;


	bind(server_socket, (struct sockaddr *) &server_adress, sizeof(server_adress));

	listen(server_socket, 5);

	int client_socket;
	while(1){
		client_socket = accept( server_socket, NULL, NULL);
		send(client_socket, reponse_data, sizeof(reponse_data), 0);
		close(client_socket);
		printf("connection accepted!");
	} 


	return 0;
}

