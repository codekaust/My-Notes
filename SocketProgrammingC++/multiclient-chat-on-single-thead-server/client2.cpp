#include <stdio.h>

#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
using namespace std;


///////////////
#include <string.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#define PORT 3001 

////////////


int main(void)
{
   fd_set rfds,k;
   struct timeval tv;
   int retval;

   /* Watch stdin (fd 0) to see when it has input. */

   FD_ZERO(&rfds);
   FD_SET(0, &rfds);

   /* Wait up to five seconds. */

   tv.tv_sec = 0;
   tv.tv_usec = 0;

   k = rfds;

    ///////////////////////////////////

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

    //////////////////////

   while(true){
        retval = select(1, &rfds, NULL, NULL, &tv);
        rfds=k;

        if (retval == -1)
            perror("select()");
        else if (retval){
            //    cout<<"Data is available now.\n";
            string s;
            getline(cin, s);
            cout<<s;

            if(s=="exit"){
                std::cout<<"Close Socket"<<std::endl;
                close(sock);
                break;
            }

            char* request  = (char *)(s.c_str());
            std:: cout<<request;
            send(sock, request, strlen(request), 0);            
            /* FD_ISSET(0, &rfds) will be true. */
        }
        
        int valread;

        valread = read(sock, buffer, 1024);
        std::cout<<"RESPONSE: "<<buffer<<std::endl;
	}

   exit(EXIT_SUCCESS);
}