#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 

#define PORT 3001 

#include <iostream>
#include <string>

using namespace std;

int main(void) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1025] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form 
    if (inet_pton(AF_INET, "127.0.0.1", & serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr * ) & serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }


    fd_set rfds;
    struct timeval tv;
    int retval;

    // FD_ZERO(&rfds);
    // FD_SET(0, &rfds);
    // FD_SET(sock, &rfds);

    // save_rfds = rfds;

    tv.tv_sec = 0;
    tv.tv_usec = 0;

    while (true) {
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        FD_SET(sock, &rfds);

        retval = select(sock+1, & rfds, NULL, NULL, & tv);
        // rfds = save_rfds;

        if (retval == -1)
            perror("select()");
        else if (FD_ISSET(0, &rfds)) {

            string s;
            getline(cin, s);

            if (s == "exit") {
                std::cout << "Close Socket" << std::endl;
                close(sock);
                break;
            }

            char * request = (char * )(s.c_str());
            send(sock, request, strlen(request), 0);
        }else if(FD_ISSET(sock, &rfds))
        {
            int valread;

            valread = read(sock, buffer, 1024);
            buffer[valread] = '\0';
            printf("response: %s\n",buffer);

            // *buffer = {0};
        }
    }

    exit(EXIT_SUCCESS);
}