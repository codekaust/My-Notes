# Explainations 
Taken from [here](https://medium.com/mobile-development-group/simple-servers-cc465f340658).

## Server
1. **Create** a new Socket and get its file descriptor.
    * `Domain`: Protocol family to be used (`AF_INET`)
    * `Type`: Communication strategy (`SOCK_STREAM`)
    * `Protocol`: The protocol to be used in the family with the socket type (`0`)

2. Set the **options** for the socket.
    * `Level`: The level of the options to be set. Use `SOL_SOCKET` for socket level options
    * `Option_name`: The name for the option to be passed to the protocol. Options like `SO_REUSEADDR` shall override checks previous occupation of the same port
    * `Option_value`: Set the value of the option to the value pointed

3. Use the `sockaddr_in` struct to get and store the details of the connection.
    * `sin_family`: Address family (`AF_INET`) 
    * `sin_port`: The port to use in 16-bit Network Byte Order (use `htons`)
        * Why `serv_addr.sin_port = htons(portno);` and not use directly portno? The reason is most devices store numbers in big-endian format, but some also do in little-endian format [meaning that the least significant byte comes first]. The htons() function makes sure that numbers are stored in memory in network byte order, which is with the most significant byte first, so the name h[host]-to-n[network]-s[short, ports are in short].
    * `sin_addr`: The IP address in 32-bit Network Byte Order (use `INADDR_ANY` to connect to any network interface or `INADDR_LOOPBACK` to connect to `127.0.0.1`). 
    * `sin_zero`: Set it to `0`

> *Address in sin_addr in server tells, from which IP will the server receive connection? And in client, it is address of server where the client will send its request.*

4. **Bind** the socket to the `IP:port`.
    * `Address`: The interface IP address to bind
    * `Port`: The port to bind to

5. **Listen** to the Socket.
    * `Backlog`: The maximum length, to which the queue of pending connections not established yet, may grow (`1 - 128` (system dependent))

    *The Server has been established! and it is listening to incoming requests*
    Now, in an infinite loop,
6. **Accept** the first new incoming connection request and **create** a new socket with the new descriptor referring to it.
    * `Address`: Details of the connection stored above

7. As the connection is established, **read** the data from the file descriptor. Convert the received bytes data to String if required.
    * `Count`: Read the next count bytes from the file descriptors
    * `Buffer`: Store them is a buffer to process it
    * `Flags`: Additional details for reading

8. **Send** a message to the client in bytes.
    * `Socket`: The new connection file descriptor to send the bytes to
    * `Message`: The message to be sent in bytes

9. **Close** the new file descriptor to close the connection.

## Client# Client
1. Follow step 1 and 3 from the steps above to **create** a new socket for the client and establish address config to use. Use the same port as in Server and set IP as `127.0.0.1` if required. You might need `inet_pton` to do so. It converts String address `127.0.0.1` into network address to be used. This is stored in the `sin_addr` object.
2. **Connect** to the already running server at the same port using the address config and the socket.
3. **Read** and **send** the data from the socket similar to step 7 and 8 above.
4. **Close** the socket whenever required.