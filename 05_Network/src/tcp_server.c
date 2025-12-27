#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // For sockaddr_in

#define PORT 12345 // Port number for the server
#define BACKLOG 5 // Number of connections allowed on the queue

int main()
{

//step 1: 创建一个socket
    // create a TCP socket
    // param1: 协议族（AF_INET 表示 IPv4） AF_INET6 - IPv6协议族 / AF_UNIX - 本地通信协议族
    // param2: 套接字类型（SOCK_STREAM 表示 TCP，SOCK_DGRAM 表示 UDP, SOCK_RAW 表示原始套接字）
    // param3: 协议（通常设为 0，表示使用默认协议）
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    //create a UDP socket
    // int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("create socket failed");
        return 1;
    }
    printf("Created socket with file descriptor: %d\n", sock_fd);

//step 2: bind the socket to an address
    // Note: 绑定通常在服务器端完成。
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
        perror("bind Failed");
        return 1;
    }
    printf("Socket bound to address successfully.\n");

//step 3: listen for incoming connections (for TCP sockets)
    // Note: Listening is also typically done on the server side.
    // socket创建的是主动套接字，需要通过listen函数将其转换为被动(监听)套接字
    // 以便接受客户端的连接请求。
    // param2: backlog，指定在拒绝连接之前，操作系统可以挂起的最大连接数目
    if (listen(sock_fd, BACKLOG) < 0) {
        perror("listen");
        return 1;
    }
    printf("Socket is ready to listen for incoming connections.\n");

//step 4: accept incoming connections (for TCP sockets)
    // Note: Accepting connections is done on the server side.
    // param2和3用于获取连接客户端的地址信息
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    while(1)
    {
        printf("Socket is ready to accept incoming connections.\n");
        int client_sock = accept(sock_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_sock < 0) {
            perror("accept failed   ");
            return 1;
        }
    // step 5: send data to client (for TCP sockets)
        // Note: Sending data can be done on both client and server sides.
        const char *message = "Hello from server!";
        ssize_t bytes_sent = send(client_sock, message, strlen(message), 0);
        if (bytes_sent < 0) {
            perror("send failed");
            return 1;
        }
        printf("Sent %zd bytes to client.\n", bytes_sent);
        close(client_sock);
    }
    

//step 5:recv data from client (for TCP sockets)
    // Note: Receiving data can be done on both client and server sides.
    // char buffer[1024];
    // size_t bytes_received = recv(client_sock, buffer, sizeof(buffer) - 1, 0);
    // if (bytes_received < 0) {
    //     perror("recv failed");
    //     return 1;
    // }
    // buffer[bytes_received] = '\0'; // Null-terminate the received data
    // printf("Received %zd bytes: %s\n", bytes_received, buffer);

// use close or shutdown to close the socket
// shutdown(sock_fd, SHUT_RDWR); // Shutdown the socket for both reading and writing
// both close and shutdown can be used to close the socket , we can use "man close/shutdown" to see the difference
    close(sock_fd);
    return 0;
}
