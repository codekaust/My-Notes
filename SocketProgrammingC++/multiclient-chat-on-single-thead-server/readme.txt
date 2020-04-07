NOTE:
1. PORT on which server binds: 3001
2. Client sends connect request on ip: 127.0.0.1, port: 

If this port is currently being used on your system, pleae change macro PORT in server.cpp and client.cpp.

Instructions to run this chat service:

    - Compile and generate executables for client and server.
      Command:
      g++ server.cpp -o server.out
      g++ client.cpp -o client.out
    
    - Run server
      Command: ./server.out
    
    - Run multiple instances of client by running the following command in multiple terminals.
      Command: ./client.out
      
Now, each client will be assigned a name and user can send messages between clients.

Max 30 clients can connect at a time.

Client can connect and disconnect at any time (like irc), server will keep running.
If server shuts down, all clients are automatically disconnected.