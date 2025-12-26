#include <stdio.h>

typedef int (*func_ptr)(int,int);
int add (int x, int y)
{
    return x + y ;
}

int mul (int x, int y)
{
    return x * y ;
}

// int op(int (*func) (int,int),int x, int y)
// {
//     return func(x,y);
// }

int op(func_ptr f,int x, int y)
{
    return f(x,y);
}

int main()
{
    printf("3 + 4 : %d \n" , op(add , 3, 4));
    printf("3 * 4 : %d \n" , op(mul , 3, 4));
}
