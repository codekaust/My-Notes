#include <stdio.h> 
#include <sys/select.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 3001 

#include <iostream>
#include <string>
#include <stdlib.h>









#include <stdio.h>

#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string>
using namespace std;

int main(){
    int sock=0;
    struct sockaddr_in serv_addr;
    char buffer[1025] = {0};

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

    fd_set readfds, savefds;
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);
    
    savefds = readfds;  

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    int ret;

    while(true){ 
        ret =     select(1, &readfds, NULL,NULL, &timeout);
        if(ret == -1){
            cout<<"NONO"<<endl;
            break;
            }
        else if (ret) {
            std::cout<<"HEHAHHAH";

            std::string in;
            std::cin>>in;            
            
            if(in=="exit"){
                std::cout<<"Close Socket"<<std::endl;
                // close(sock);
                break;
            }

            char* request  = (char *)(in.c_str());
            std:: cout<<request;
            send(sock, request, strlen(request), 0);
        }
        readfds = savefds;
        
        int valread;

        valread = read(sock, buffer, 1024);
        std::cout<<"RESPONSE: "<<buffer<<std::endl;
    }
    return 0;
}