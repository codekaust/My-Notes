#include <stdio.h>  
#include <string.h>   
#include <stdlib.h>  
#include <errno.h>  
#include <unistd.h>     
#include <arpa/inet.h> 

#include <string>
#define PORT 3001

int main(){
    int opt = 1;   
    int master_socket, addrlen, new_socket, client_sockets[30] = {0}, max_clients = 30;
    int activity, valread;   
    int sd, max_sd;   //socket descriptor
    struct sockaddr_in address;   
         
    char buffer[1025] = {0};  //data buffer of 1K  
         
    //create a master socket to accept new connections from clients
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)   
    {   
        perror("socket failed");   
        exit(EXIT_FAILURE);   
    }   
     
    //set master socket options (allow multiple connections)
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )   
    {   
        perror("setsockopt");   
        exit(EXIT_FAILURE);   
    }   
     
    //setup address struct
    address.sin_family = AF_INET;   
    address.sin_addr.s_addr = INADDR_ANY;   
    address.sin_port = htons( PORT );   

    addrlen = sizeof(address);   
         
    //bind the socket to localhost port PORT  
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)   
    {   
        perror("bind failed");   
        exit(EXIT_FAILURE);   
    }
              
    //try to specify maximum of 3 pending connections for the master socket  
    if (listen(master_socket, 3) < 0)   
    {   
        perror("listen");   
        exit(EXIT_FAILURE);   
    }   
         
    //inform server status
    printf("Listening on port %d.\nWaiting for connections...\n", PORT);

    //set of socket descriptors used in select function (to handle simultaneous incoming requests)
    fd_set readfds;
    
    while(true)
    {   
        //clear set and add master_socket
        FD_ZERO(&readfds);
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;
             
        //add child sockets to set
        for ( int i = 0 ; i < max_clients ; i++)   
        {   
            sd = client_sockets[i];   
                 
            //check validity of socket desc.
            if(sd > 0)   
                FD_SET( sd , &readfds);   
                 
            //get highest file descriptor number for select function  
            if(sd > max_sd)   
                max_sd = sd;   
        }   
     
        //wait for an activity on one of the sockets , timeout is NULL (wait indefinitely)
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);   
       
        if ((activity < 0) && (errno!=EINTR))
            puts("select error");  
             
        //request at master socket -> accept request
        if (FD_ISSET(master_socket, &readfds))   
        {   
            if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)   
            {   
                perror("accept");   
                exit(EXIT_FAILURE);   
            }   
             
            //print new connection details
            printf("New connection details: socket_fd is %d , ip is : %s , port : %d\n" , new_socket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));
           
            //send greeting and inform client of its socket_fd number (which serves as its name)
            char greeting[1024];
            sprintf(greeting, "Successfully connected with server.\nYour socket_fd number (serves as name) is %d.\n", new_socket);  
            if(send(new_socket, greeting, strlen(greeting), 0) != strlen(greeting))      
                perror("send");   
                 
            //add new socket to array of sockets  
            for (int i = 0; i < max_clients; i++)   
            {   
                //if position is empty  
                if(client_sockets[i] == 0)   
                {   
                    client_sockets[i] = new_socket;   
                    break;   
                }   
            }   
        }   
             
        //else its some IO operation on some other socket 
        for (int i = 0; i < max_clients; i++)   
        {   
            sd = client_sockets[i];   
                 
            if (FD_ISSET(sd , &readfds))   
            {   
                //Read the incoming message  
                valread = read( sd , buffer, 1024);

                //Check for connection closing request 
                if (valread == 0)   
                {   
                    //Somebody disconnected , get his details and print  
                    printf("Client disconnected with socket_fd %d.", sd);   
                         
                    //Close the socket and mark as 0 in list for reuse  
                    close(sd);
                    client_sockets[i] = 0;   
                }
                    
                else
                {   
                    //mark string termination in buffer
                    buffer[valread] = '\0';

                    //print incoming message details
                    printf("Recieved message: %s, from socket_fd: %d\n", buffer, sd);

                    //Used while sending messages to clients
                    std::string msg_string = "Client "+std::to_string(sd)+": "+buffer;
                    char* msg = (char *)msg_string.c_str();

                    //send incoming message details to all clients
                    //socket_fd (serves as client name) is added in string showing from which client the request has been recieved
                    for(int j=0; j<max_clients; j++){
                        int temp_sd = client_sockets[j];

                        if(temp_sd != sd && temp_sd!=0){
                            send(temp_sd, msg, strlen(msg), 0 );   
                        }
                    }
                }   
            }   
        }   
    }   
         
    return 0;   
}   