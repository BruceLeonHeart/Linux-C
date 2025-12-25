#include <stdio.h>
#include <assert.h>
#include "math_operations.h"

int main() {
    printf("Running math operations tests...\n");
    
    // 测试add函数
    assert(add(2, 3) == 5);
    assert(add(-1, 1) == 0);
    assert(add(0, 0) == 0);
    printf("✓ add() tests passed\n");
    
    // 测试subtract函数
    assert(subtract(5, 3) == 2);
    assert(subtract(0, 5) == -5);
    assert(subtract(5, 5) == 0);
    printf("✓ subtract() tests passed\n");
    
    // 测试multiply函数
    assert(multiply(3, 4) == 12);
    assert(multiply(-2, 3) == -6);
    assert(multiply(0, 100) == 0);
    printf("✓ multiply() tests passed\n");
    
    // 测试divide函数
    assert(divide(10, 2) == 5);
    assert(divide(7, 2) == 3);
    assert(divide(5, 0) == 0);  // 除以零的特殊处理
    printf("✓ divide() tests passed\n");
    
    printf("\nAll tests passed! ✓\n");
    return 0;
}
