#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h> // For sockaddr_in
#include <arpa/inet.h> // For inet_pton


void test_eidian_order() {
    // This function is a placeholder to demonstrate the use of endian order.
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

    // TCP/IP defines the eidien order for network byte order as big-endian.
    // human : "172.17.242.131"  <-> network byte order: 0x83F211AC
    char  buffer[32];
    struct in_addr in;
    unsigned int address;

    // input a string representation of an IP address with "." format
    printf("Enter an IP address (e.g. 172.17.242.131): ");
    fgets(buffer, sizeof(buffer)-1, stdin);
    buffer[31] = '\0'; // Ensure null termination

    // test inet_aton function to convert string to network byte order
    if (inet_aton(buffer, &in) == 0) {
        printf("inet_aton: \tInvalid address\n");
    }
    else {
        printf("inet_aton: \t0x%x\n", in.s_addr);
    }

    // deprecated function inet_addr() to convert string to network byte order
    // 255.255.255.255 is a special case ,it will make error in inet_addr() function while not in inet_aton. 
    if ((address = inet_addr(buffer)) == INADDR_NONE) {
        printf("inet_addr: \tInvalid address\n");
    } else {
        printf("inet_addr: \t0x%x\n", address);
    }

    // inet_network function to convert string to host byte order
    if ((address = inet_network(buffer)) == -1) {
        printf("inet_network: \tInvalid address\n");
    } else {
        printf("inet_network: \t0x%x\n", address);
    }

    if (inet_ntoa(in) == NULL) {
        printf("inet_ntoa: \tInvalid address\n");
    } else {
        printf("inet_ntoa: \t%s\n", inet_ntoa(in));
    }


    // printf("Converted IP address to network byte order: 0x%08x\n", ntohl(in.s_addr));


    // This is a simple test program to demonstrate the use of socket addresses.
    // It does not perform any actual socket operations.
    
    // printf("This program is a placeholder for testing socket address structures.\n");
    
    // You can add code here to create a socket, bind it, listen, accept, or connect as needed.
    
    return 0;
}

