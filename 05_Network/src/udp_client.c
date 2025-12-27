#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define PORT 8888

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_sent, bytes_received;

    // 创建UDP套接字
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP Client connected to %s:%d\n", SERVER_IP, PORT);
    printf("Type 'exit' to quit\n");

    while (1) {
        printf("Enter message: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        
        // 移除换行符
        buffer[strcspn(buffer, "\n")] = 0;
        
        // 检查退出命令
        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // 发送数据
        bytes_sent = sendto(sockfd, buffer, strlen(buffer), 0,
                           (struct sockaddr*)&server_addr, sizeof(server_addr));
        
        if (bytes_sent < 0) {
            perror("sendto failed");
            continue;
        }

        printf("Sent %ld bytes\n", bytes_sent);

        // 等待响应（可选的）
        memset(buffer, 0, BUFFER_SIZE);
        socklen_t server_len = sizeof(server_addr);
        
        bytes_received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                                 (struct sockaddr*)&server_addr, &server_len);
        
        if (bytes_received > 0) {
            printf("Server response: %s\n", buffer);
        } else {
            printf("No response from server\n");
        }
    }

    close(sockfd);
    return 0;
}