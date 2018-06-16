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
<<<<<<< HEAD
		printf("connection accepted!");
	} 
=======

<<<<<<< HEAD
		printf("connection accepted!");
	} 

	return 0;

}
=======
	}
>>>>>>> 3c713ea60638d6c35b0801d96603d24592eb6e57


	return 0;
}
<<<<<<< HEAD

=======
>>>>>>> 4825194215a8cd9ad0214b148aee738bbfcc574f
>>>>>>> 3c713ea60638d6c35b0801d96603d24592eb6e57
