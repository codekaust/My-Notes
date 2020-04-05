// should be just like basic-server-client/server.c but should always be listening, and response based user input
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080

#include <iostream>
#include <string>

int main(){
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0))<0){
        std::cout<<("\n Socket creation error \n")<<std::endl;
        return -1;
    }

    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))){
        perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 

    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
        perror("bind fail");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }

    int new_socket;
        
    if((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                (socklen_t*)&addrlen))<0){
        perror("accept"); 
        exit(EXIT_FAILURE); 
    }

    while (true)
    {
        int valread;
        // int new_socket;
        
        // if((new_socket = accept(server_fd, (struct sockaddr *)&address, 
		// 			(socklen_t*)&addrlen))<0){
        //     perror("accept"); 
		//     exit(EXIT_FAILURE); 
        // }

        valread = read(new_socket, buffer, 1024);
        std::cout<<"REQUEST: "<<buffer<<std::endl;

        std::cout<<"RESPONSE: ";
        std::string in;
        std::getline(std::cin, in);

        if(in=="exit"){
            close(server_fd);
            break;
        }

        char* response  = (char *)(in.c_str());

        send(new_socket, response, strlen(response),0);
    }

    return 0;
}