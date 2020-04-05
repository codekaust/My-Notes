## Changes made with respect to attempt1:
**In server.cpp**:
Take the following code out of while loop:
```cpp
int new_socket;
        
if((new_socket = accept(server_fd, (struct sockaddr *)&address, 
            (socklen_t*)&addrlen))<0){
    perror("accept"); 
    exit(EXIT_FAILURE); 
}
```

**In client.cpp**:

Take the following code out of while loop:
```cpp
if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
{ 
    printf("\nConnection Failed \n"); 
    return -1; 
} 
```

**WHY?**:
Between a server and a client connection needs to be made only once, after that they can send request and response indefinitely.