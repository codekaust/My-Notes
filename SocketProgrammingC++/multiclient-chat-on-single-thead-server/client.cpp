#include <unistd.h>
#include <string.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <iostream>
#include <string>

#define PORT 3001

int main(void) {
    int client_sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1025] = {0};

    if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
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

    puts("Connecting to server...");

    if (connect(client_sock, (struct sockaddr * ) & serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    //set of file descriptor for reading
    fd_set rfds;

    //Wait for 0 secs to get input (so that messages can be sent and recieved without pausing the code (in realtime))
    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    //activity returned by select function
    int activity;

    while (true) {

        FD_ZERO(&rfds);
        //file desc for stdin
        FD_SET(0, &rfds);
        //file desc for socket
        FD_SET(client_sock, &rfds);

        activity = select(client_sock+1, & rfds, NULL, NULL, & tv);

        if (activity == -1)
            perror("select()");
        
        //check if something happened in stdin (user input) file descriptor -> read stdin and send to server
        else if (FD_ISSET(0, &rfds)) {
            std::string s;
            getline(std::cin, s);

            if (s == "exit") {
                std::cout << "Closing Socket..." << std::endl;
                close(client_sock);
                break;
            }

            char * request = (char * )(s.c_str());
            send(client_sock, request, strlen(request), 0);
        }
        
        //check if something happened in socket file descriptor -> recieved a message
        else if(FD_ISSET(client_sock, &rfds))
        {
            int valread = read(client_sock, buffer, 1024);

            //server disconnected
            if(valread==0){
                puts("Server Disconnected.\n");
                return 0;
            }

            //mark string termination in buffer
            buffer[valread] = '\0';
            
            printf("%s\n",buffer);

            // *buffer = {0};
        }
    }

    return 0;
}