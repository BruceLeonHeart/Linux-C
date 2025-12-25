#include <stdio.h>
#include "utils.h"

void print_welcome() {
    printf("========================================\n");
    printf("     Welcome to My Project!\n");
    printf("========================================\n");
}

void debug_print(const char* message) {
    printf("[DEBUG] %s\n", message);
}
