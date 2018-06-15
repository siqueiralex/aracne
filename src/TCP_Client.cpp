#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>


int main(){

	char request[256] = "Test Data";

	//create a socket
	int client_socket;
	client_socket = socket(AF_INET, SOCK_STREAM, 0);

	// specify an adress for the socket
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;
	int connection_status = connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	if (connection_status==-1){
		printf("There was an error connecting with the server");
	}

	//send(client_socket, request, sizeof(request), 0);

	char buffer[256];
	recv(client_socket, &buffer, sizeof(buffer), 0);
	
	printf("%s \n", buffer);
	close(client_socket);

	return 0;
}