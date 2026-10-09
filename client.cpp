# include <iostream>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <cstring>

using namespace std;

int main(){
	int domain = AF_INET;
	int type = SOCK_STREAM;
	int protocol = 0;

	char buffer[256]; // This will allow me to make my string

	struct sockaddr_in server;
	server.sin_family = domain;

	int port = htons(6000);
	server.sin_port = port;
	
	server.sin_addr.s_addr = inet_addr("172.16.158.130");

	int client_socket = socket(domain, type, protocol);

	int connection = connect(client_socket, (const struct sockaddr *) &server, sizeof(server));
	cout << "Enter a message: ";
	
	if (fgets(buffer,255,stdin) != NULL){ // inputting message
		ssize_t sending =  send(client_socket, buffer, strlen(buffer), 0);

		if (sending == -1) {
			perror("send");
		}
	}

	// int writing = write(client_socket, buffer, strlen(buffer));

	// writing = read(client_socket, buffer, 255);

	close(client_socket);

	return 0;
}
