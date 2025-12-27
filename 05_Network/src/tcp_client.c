#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
// ---- 1. 创建套接字 ----
    // param1: 协议族（AF_INET 表示 IPv4） AF_INET6 - IPv6协议族 / AF_UNIX - 本地通信协议族
    // param2: 套接字类型（SOCK_STREAM 表示 TCP，SOCK_DGRAM 表示 UDP, SOCK_RAW 表示原始套接字）
    // param3: 协议（通常设为 0，表示使用默认协议）
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0); // 创建一个 TCP 套接字
    if (sock_fd < 0) {
        perror("create socket failed");
        return 1;
    }

// ---- 2. 创建目的套接字地址 ----
    // struct sockaddr 通用的套接字地址结构
    // 但是对于不同的协议族（如 IPv4、IPv6），需要使用特定的结构体
    // 例如，IPv4 使用 struct sockaddr_in，IPv6 使用 struct sockaddr_in6
    struct sockaddr_in sock;
    sock.sin_family = AF_INET;
    sock.sin_port = htons(12345); // 字节顺序转换函数
    // inet_aton 与 inet_addr(无法处理255.255.255.255) 类似，但更安全，推荐使用 inet_aton
    sock.sin_addr.s_addr = inet_aton("127.0.0.1"); // Bind to any address
    memset(sock.sin_zero, 0, sizeof(sock.sin_zero)); // 填充字节

// ---- 3. 建立连接 ----
    // 连接到服务器的地址和端口
    if(connect(sock_fd,(struct sockaddr*)&sock,sizeof(struct sockaddr_in)) < 0) {
        perror("connect failed");
        return 1;
    }
    printf("Connected to server successfully.\n");

// ---- 4. 接受数据 ----
    char buffer[1024];
    size_t bytes_received = recv(sock_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received < 0) {
        perror("recv failed");
        return 1;
    }
    buffer[bytes_received] = '\0'; // Null-terminate the received data
    printf("Received %zd bytes: %s\n", bytes_received, buffer);
// ---- 5. 关闭套接字---
    close(sock_fd);
    return 0;
}