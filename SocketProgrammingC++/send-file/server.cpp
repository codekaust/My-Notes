//Recieves and writes to new file.

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#define PORT 8080

#include <iostream>
#include <string>
#include <fstream>

const static int BUF_SIZE = 1024;
using std::ios_base;

int main(int argc, char** argv){
    int server_fd;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUF_SIZE] = {0};
    
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
    }else
	{
		std::cout<<"Socket Connected"<<std::endl;
	}
	

    std::ofstream out(argv[1], ios_base::out | ios_base::binary);

    while(true) {
        int valread;

        valread = read(new_socket, buffer, BUF_SIZE);

		//client disconnects
		if(valread==0){
			close(new_socket);
			break;
		}

		std::cout<<buffer<<std::endl;

        out.write(&buffer[0], BUF_SIZE);
    }        

    out.close();  

    return 0;
}