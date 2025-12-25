#include <pthread.h>
#include <unistd.h> //man 3 sleep
#include <stdio.h>

void* myturn(void* args)
{
    int* ptr = (int*)args;
    for(int i=0; i<5; i++)
    {
       sleep(1);
       printf("My %d Turn \n",i);

       // update input value
       (*ptr)++;
       printf("update input as %d \n",*ptr);

    }
    return NULL;
}
void yourturn()
{
    for(int i=0; i<5; i++)
    {
       sleep(1);
       printf("Your %d Turn \n",i);
    }
}

int main()
{
    pthread_t thread;

    int input = 5;
   // pass input value into thread
    pthread_create(&thread,NULL,myturn,(void*)&input);
 
    yourturn();

    pthread_join(thread,NULL);

    printf("Final input %d \n",input);
    return 0;
}
