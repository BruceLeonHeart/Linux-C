
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc,char** argv)
{
    //校验使用方法
    if (argc != 3) 
    {
        printf("Usage: %s <file_path> <mode>\n", argv[0]);
        return -1;
    }

    //方式1 手动将传进来的10进制字符串转换为8进制数
    int mode = atoi(argv[2]);
    if(mode < 0 || mode > 777)
    {
        printf("Mode must be between 000 and 777\n");
        return -1;
    }
#if 0
    // 所有者/组/其他 
    int u = mode / 100;
    int g = (mode / 10) % 10;
    int o = mode % 10;
    mode_t m = u * 64 + g * 8 + o;
#endif
    //方式2 直接将传进来的8进制字符串转换为8进制数
    mode_t m = strtol(argv[2], NULL, 8);
    //获取命令行参数
    const char* file_path = argv[1];
    //修改文件权限
    if (chmod(file_path, m) == -1)
    {
        perror("chmod failed");
        return -1;
    }
    else
    {
        printf("File permissions of '%s' changed to %o successfully.\n", file_path, mode);
        return 0;
    }
}