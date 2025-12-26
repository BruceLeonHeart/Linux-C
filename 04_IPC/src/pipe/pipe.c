#include <stdio.h>
#include <unistd.h>


int main()
{
    int fd[2];

    // create a pipe

    if(pipe(fd) == -1)
        perror()


    return 0;

}