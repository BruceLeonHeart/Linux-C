//标准输入输出流，包含fopen
#include <stdio.h>
//文件状态
#include <sys/stat.h>
//内存分配
#include <stdlib.h>

//小写转大写并进行输出
int convert(){
    FILE *fp;
    struct stat statbuff; /*文件状态存储结构*/
    char *p,*q;
    int n;
    //获取文件状态
    int res = -1;
    if(stat("test.txt",&statbuff) == -1){
        // printf("fail to get stat");
        perror("fail to get stat");
        return res;
    }
    printf("file contains %ld chars \n",statbuff.st_size);
    //打开文件
    fp = fopen("test.txt","rb");
    if(fp == NULL){
        perror("fail to open");
        return res;
    }
    
    //动态分配保存内容的缓冲区，如果失败表示内存分配失败，关闭文件即可
    //这里多分配一个char 存一个"\0" 来表示结束
    p = (char *)malloc(sizeof(char) * (statbuff.st_size +1));
    if(p== NULL){
        perror("fail to malloc");
        goto err1;
    }

    //读取文件内容，如果失败，则释放缓冲区，且关闭文件
    n = fread(p,sizeof(char),statbuff.st_size,fp);
    //printf("file contains %d chars 2 \n",n);
    if(n==-1){
        perror("fail to read");
        goto err2;
    }
    *(p+n)='\0'; //设置结束标志
    q = p;
    while (*q != '\0')
    {
        if('a' <=*q && *q <= 'z' )  (*q) -=32;
        printf("%c",*q);
        q++;
    }
    res = 0;

err2:
    free(p);    
err1:
    fclose(fp);
    return res;
}

int main(){
    // printf("Hello \n");
    if(convert() !=0) printf("convert failed \n");
    return 0;
}