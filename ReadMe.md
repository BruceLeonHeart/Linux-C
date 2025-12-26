## Description

Linux C下的编程实践

### Linux下系统编程

这里是指 程序员使用系统调用或C语言本身携带的库函数来设计和编写程序

- shell命令是OS提供给普通用户使用的接口
- 系统调用是OS提供给程序员使用的接口
- C语言函数库基于系统调用实现，封装了系统调用
- gcc链接常用的库,如libc.so.6
- 不自动链接将 -l<库名>-L<库目录>
- man 1(exe)/2(System call)/3(LIB) lseek
