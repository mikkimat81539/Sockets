# include <sys/socket.h>
# include <netinet/in.h>
# include <csignal>


# include <iostream>

using namespace std;


// For keyboard interruptions
void keyboard_interrupt(int){
	cout << "\nServer Shutdown" << endl;
	exit(0);
}


int main(){
	signal(SIGINT, keyboard_interrupt);
	

	int domain = AF_INET;
	int type = SOCK_STREAM;
	int protocol = 0;	

	int port = htons(6000);

	int backlog =  5; // # of income request can be waiting in the queue.

	struct sockaddr_in address;
	address.sin_family = domain;
	address.sin_port = port;

	address.sin_addr.s_addr = INADDR_ANY;

	socklen_t address_len = sizeof(address);	


	while(true){
	
		int server_socket = socket(domain, type, protocol);

		int socket_bind = ::bind(server_socket, (const struct sockaddr *) &address, sizeof(address));

		int server_listen = listen(server_socket, backlog);
		
		
		int server_accept =  accept(server_socket, nullptr, nullptr);


		char buffer[1024] = {0};

		ssize_t receive_msg = recv(server_accept, buffer, sizeof(buffer), 0);

		buffer[receive_msg] = '\0';
		

		cout << "Message from Client: " << buffer << endl;


		// Catch errors for making socket
		if (server_socket < 0){
			cout << "Server not made" << endl;
		}

		// Catch errors for binding
		else if (socket_bind < 0){
			cout << "Server not binded" << endl;
		}

		
		// Catch errors for listening
		else if (server_listen < 0){
			cout << "Server not listening" << endl;
		}

		
		else if (server_accept < 0){
			cout << "Server not accepted" << endl;
		}

		else if (receive_msg < 0){
			cout << "Message not received" << endl;
		}	
	
	}	

	return 0;
}
