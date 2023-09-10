#include <stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

#define PORT 8080

int main (int argc,char const*argv[]){
	int sock=0, valread;
	struct sockaddr_in serv_addr;
	char *hello= "Hello from Kishor client";
	char buffer[1024]={0};
	if ((sock=socket(AF_INET,SOCK_STREAM,0))<0){
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(PORT);

	//Convert IPv4 and IPv6 address from text to binary form
	//convert an IP address in its text from (such as “192.0.2.1”) to its binary representation in network byte order, which is needed for may networking operations such as creating a socket, binding a socket to a specific address, or connecting to a remote host.

	if (inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<=0){
	    printf("\n Invalid address/ Address not supported \n");
        return -1;
    }

    //connect () function iis used to establish a connection between a client socket and a server socket. The function is used by the client to initiate a connection request to the fserver, and once the connection is established , the two sockets can communicate bidirectionally

    //The connect() function takes three arguments:
    // The first is the file descriptor of the client socket
    // The second is a pointer to the address of the socket to which the client wants to connect, and the third is the size of the 
    if (connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
	    printf("\n Connection Failed\n");
	    return -1;
    }

    send (sock,hello,strlen(hello),0);
    printf("Hello message sent\n");
    valread=read(sock,buffer,1024);
    printf("%s\n",buffer);
    return 0;
}
