// This block of code includes the necessary headers fo socket programming,
// standard input/output, and string manipulation.
// It also defines the port number to use for the sever
// to listen for incomming connectiont
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8080
// This is the main function of the server program.
// It declares variables for the socket file descripter,
// the new socket file descripter, the address of the server,
// the length of the address, a buffer for receiving data,
// and a message to sennd to the client.
int main (int argc, char const *argv[]){
    int server_fd,new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    // Creating socket file descripter
    // This code creates a socket file descripter using the socket() system call
    // It uses the AF_NET address family to specify IPv4,
    // SOCK_STREAM as the socket type for a TCP connection can be SOCK_DGRAM
    // For UDP connection , and 0 as the protocol argument.

    // Int socket(int domain,int type, int protocol)

    if((server_fd=socket(AF_INET,SOCK_STREAM,0))==0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // setup address structure for the server
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // int bind (int socketfd,struct socketaddr *my_addr, socket_t addrlen)
    // Bind the socket to the address
    if (bind(server_fd,(struct sockaddr *)&address,sizeof(address))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for incomming connection
    // int listen(int socket_fd,int backlog)-> backlog is a max length of the pending connection
    if (listen(server_fd,3)<0){
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    // Accept incoming connection and handle them
    if ((new_socket=accept(server_fd,(struct sockaddr*)&address,(socklen_t*)&addrlen))<0) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }

    // Read data from the client
    int valread = read(new_socket, buffer, 1024);
    printf("%s\n", buffer);

    // Send a message back to the client
    send(new_socket,hello,strlen(hello),0);
    printf("Hello message send\n");

    return 0;
}