// Client sends file.

#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 

#include <iostream>
#include <string>
#include <fstream>

const static int BUF_SIZE = 1024;

int main(int argc, char** argv){
    int sock=0;
    struct sockaddr_in serv_addr;
    char buffer[BUF_SIZE] = {0};

    if((sock = socket(AF_INET, SOCK_STREAM, 0))<0){
        printf("\n Socket creation error \n"); 
		return -1; 
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 

    //for reading file
    std::ifstream in(argv[1], std::ios_base::in | std::ios_base::binary);

    do{

        in.read(&buffer[0], BUF_SIZE);      // Read at most n bytes into
        send(sock, buffer, BUF_SIZE, 0);
    } while (in.gcount() > 0);  

	close(sock);

    in.close();

    return 0;
}