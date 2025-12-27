#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h> // For sockaddr_in
#include <arpa/inet.h> // For inet_pton


void test_eidian_order() {
    // use 0x01020304 to test endian order.
    unsigned int test_value = 0x01020304;
    unsigned char *byte_ptr = (unsigned char *)&test_value;
    printf("Testing endian order:\n");
    printf("Byte 0: %02x\n", byte_ptr[0]);
    printf("Byte 1: %02x\n", byte_ptr[1]);
    printf("Byte 2: %02x\n", byte_ptr[2]);
    printf("Byte 3: %02x\n", byte_ptr[3]);
    // big endian means the most significant byte is stored at the lowest address.
    // little endian means the least significant byte is stored at the lowest address.
    // 大端序意味着最高有效字节存储在最低地址。
    // 小端序意味着最低有效字节存储在最低地址。
    if (byte_ptr[0] == 0x04) {
        printf("System is little-endian.\n");
    } else if (byte_ptr[0] == 0x01) {
        printf("System is big-endian.\n");
    } else {
        printf("Unknown endian order.\n");
    }
}

int main() {
    test_eidian_order();    
}

