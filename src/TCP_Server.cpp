#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>


int main(){
	
	char message[256] = "You have reached the server!";

	//create a socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// define server adress
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// bind the socket to the adress	
	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	listen(server_socket, 5);

	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);

	//send message
	send(client_socket, message, sizeof(message), 0);

	// close the socket
	close(server_socket);

	return 0;
}