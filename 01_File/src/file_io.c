
// 在编写跨平台的文件I/O代码时，优先使用标准C库函数，如 fopen、fread、fwrite 和 fclose。
// Linux 系统调用（如 open、read、write 和 close）使用文件描述符来标识文件，是Unix/Linux特有的接口。

// Linux C 创建/打开/关闭文件示例
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    // 使用 open 创建/打开文件
    int fd = open("example.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        perror("Error opening/creating file");
        return -1;
    }

    // 使用 write 向文件写入数据
    const char *data = "Hello, Linux File I/O!\n";
    ssize_t bytes_written = write(fd, data, 22);
    if (bytes_written == -1)
    {
        perror("Error writing to file");
        close(fd);
        return -1;
    }

    // 使用 lseek 将文件偏移量移动到文件开头
    if (lseek(fd, 0, SEEK_SET) == -1)
    {
        perror("Error seeking in file");
        close(fd);
        return -1;
    }

    // 使用 read 从文件读取数据
    char buffer[23] = {0};
    ssize_t bytes_read = read(fd, buffer, 22);
    if (bytes_read == -1)
    {
        perror("Error reading from file");
        close(fd);
        return -1;
    }

    // 输出读取的数据
    printf("Read from file: %s", buffer);

    // 使用 close 关闭文件
    if (close(fd) == -1)
    {
        perror("Error closing file");
        return -1;
    }

    return 0;
}