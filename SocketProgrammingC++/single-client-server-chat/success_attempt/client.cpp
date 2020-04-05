#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 

#include <iostream>
#include <string>

int main(){
    int sock=0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

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

    while(true){
        // if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
        // { 
        //     printf("\nConnection Failed \n"); 
        //     return -1; 
        // } 

        int valread;

        std::cout<<"REQUEST: ";
        std::string in;
        std::getline(std::cin, in);

        if(in=="exit"){
            std::cout<<"Close Socket"<<std::endl;
            close(sock);
            break;
        }

        char* request  = (char *)(in.c_str());
        send(sock, request, strlen(request), 0);
        valread = read(sock, buffer, 1024);
        std::cout<<"RESPONSE: "<<buffer<<std::endl;
    }
    return 0;
}