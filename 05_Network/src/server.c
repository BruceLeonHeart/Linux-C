#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // For sockaddr_in

#define PORT 12345 // Port number for the server
#define BACKLOG 5 // Number of connections allowed on the queue

int main()
{

//step 1: create a socket
    // create a TCP socket
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    //create a UDP socket
    // int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("socket");
        return 1;
    }
    printf("Created socket with file descriptor: %d\n", sock_fd);
//step 2: bind the socket to an address
    // Note: Binding is typically done on the server side, not the client side.
    // For a server, you would use bind() to associate the socket with an IP address and port.
    // For a client, you usually connect to a server's address.
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT); // Port number
    // For a specific address, you can use inet_pton() to convert a string to an address.
    server_addr.sin_addr.s_addr = INADDR_ANY; // Bind to any address (As server might own multiple IPs dute to multiple network interfaces)
    // sockaddr defines a generic socket address structure. while sockaddr_in is specifically for IPv4 addresses(TCP/IP).
    // so we made a conversion from sockaddr to sockaddr_in here. 
    if (bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        return 1;
    }
    printf("Socket bound to address successfully.\n");
//step 3: listen for incoming connections (for TCP sockets)
    // Note: Listening is also typically done on the server side.
    if (listen(sock_fd, BACKLOG) < 0) {
        perror("listen");
        return 1;
    }
    printf("Socket is ready to listen for incoming connections.\n");
//step 4: accept incoming connections (for TCP sockets)
    // Note: Accepting connections is done on the server side.
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_sock = accept(sock_fd, (struct sockaddr *)&client_addr, &client_len);
    if (client_sock < 0) {
        perror("accept");
        return 1;
    }
    printf("Socket is ready to accept incoming connections.\n");
//step 5: connect to a server (for client sockets)
    // Note: Connecting is done on the client side.
    // struct sockaddr_in server_addr;
    // server_addr.sin_family = AF_INET;
    // server_addr.sin_port = htons(12345); // Port number
    // inet_pton(AF_INET, "

// use close or shutdown to close the socket
// shutdown(sock_fd, SHUT_RDWR); // Shutdown the socket for both reading and writing
// both close and shutdown can be used to close the socket , we can use "man close/shutdown" to see the difference
    close(sock_fd);
    close(client_sock);
    return 0;
}
