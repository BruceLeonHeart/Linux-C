#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


#define STB_IMAGE_IMPLEMENTATION  // 必须定义这个宏
#include <stb_image.h>

#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define PORT 8888

// 分包头
/*
确定分包大小（MSS）
为了避免 IP 层分片（Fragmentation）导致的丢包率激增，单次发送的 UDP 负载应控制在 MTU（通常为 1500 字节） 以下。
安全建议值：建议单包数据长度设为 1400 字节 左右，预留空间给 IP 头和 UDP 头。

字段	大小	说明
Sequence ID	4 字节	这一帧数据的唯一标识（防止不同帧的数据混淆）
Packet Index	2 字节	当前分包的序号（从 0 开始）
Total Packets	2 字节	这一帧总共有多少个分包
Data Offset	4 字节	该数据在全局 Buffer 中的偏移量（可选）

#define CHUNK_SIZE 1400

void send_large_data(int sock, struct sockaddr_in *addr, unsigned char *buffer, int total_len) {
    int total_packets = (total_len + CHUNK_SIZE - 1) / CHUNK_SIZE;
    uint32_t frame_id = get_next_frame_id(); // 帧序号自增

    for (int i = 0; i < total_packets; i++) {
        unsigned char packet[1500];
        int offset = i * CHUNK_SIZE;
        int current_chunk_size = (total_len - offset) < CHUNK_SIZE ? (total_len - offset) : CHUNK_SIZE;

        // 1. 填充头部
        memcpy(packet, &frame_id, 4);
        memcpy(packet + 4, &i, 2);
        memcpy(packet + 6, &total_packets, 2);
        
        // 2. 填充数据
        memcpy(packet + 8, buffer + offset, current_chunk_size);

        // 3. 发送
        sendto(sock, packet, current_chunk_size + 8, 0, (struct sockaddr*)addr, sizeof(*addr));
    }
}

4. 接收端逻辑（Receiver）
接收端需要一个临时缓冲区来暂存属于同一帧的分包，直到所有分包到齐。
解析头部：提取 frame_id, index, total。
定位存储：根据 index * CHUNK_SIZE 将数据拷贝到全局大 Buffer 的对应位置。
计数与校验：使用位图（Bitmap）或计数器记录收到的包数。当 count == total 时，触发应用层处理该帧。
超时处理：如果某一帧的部分包丢失，长时间未集齐，则丢弃该帧，释放缓冲区。
5. 2026 年的高级方案建议
流控与拥塞控制：直接在全局区猛发大量 UDP 包会导致路由器丢包。建议在发送包之间加入微小的 usleep，或者实现简单的滑动窗口机制。
使用现有库：如果业务允许，建议使用 enet 或 KCP。这些库在 UDP 基础上实现了可靠的分包、重传和组包，能极大地减少你手动处理 stbi_load 之后的大像素数据时的出错率。
FEC 前向纠错：如果是传输图像，可以考虑每发送 10 个数据包多发 2 个冗余校验包，这样即使丢了 1-2 个包，接收端也能还原数据而无需重传。




*/
#define CHUNK_SIZE 1400

struct MetaData {
    uint32_t sequence_id;
    uint16_t packet_index;
    uint16_t total_packets;
    uint32_t data_offset;
};



int main() {

    // read imgage using stb_image
    int w, h, n;
    unsigned char* temp_data = stbi_load("asuna.jpg", &w, &h, &n, 0);
    if (temp_data == NULL) {
        fprintf(stderr, "Failed to load image\n");
        return -1;
    }
    printf("Image loaded: width=%d, height=%d, channels=%d\n", w, h, n);

    ssize_t img_size = w * h * n;
    printf("Image size in bytes: %ld\n", img_size);

    // 分包


#if 1
    int sockfd;
    struct sockaddr_in server_addr;
    //char buffer[BUFFER_SIZE];
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
    // printf("Type 'exit' to quit\n");

    while (1) {
        // printf("Enter message: ");
        // fgets(buffer, BUFFER_SIZE, stdin);
        
        // // 移除换行符
        // buffer[strcspn(buffer, "\n")] = 0;
        
        // // 检查退出命令
        // if (strcmp(buffer, "exit") == 0) {
        //     break;
        // }

        // 发送数据
        bytes_sent = sendto(sockfd, 
                            temp_data, 
                            img_size,
                            0,
                           (struct sockaddr*)&server_addr, sizeof(server_addr));
        
        if (bytes_sent < 0) {
            perror("sendto failed");
            continue;
        }

        printf("Sent %ld bytes\n", bytes_sent);

        // 等待响应（可选的）
        #if 0
        memset(buffer, 0, BUFFER_SIZE);
        socklen_t server_len = sizeof(server_addr);
        
        bytes_received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                                 (struct sockaddr*)&server_addr, &server_len);
        
        if (bytes_received > 0) {
            printf("Server response: %s\n", buffer);
        } else {
            printf("No response from server\n");
        }
        #endif
    }

    close(sockfd);
#endif
    stbi_image_free(temp_data);
    return 0;
}