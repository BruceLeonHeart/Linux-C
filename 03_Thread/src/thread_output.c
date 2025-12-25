#include <pthread.h>
#include <unistd.h> //man 3 sleep
#include <stdio.h>
#include <stdlib.h>

void* myturn(void* args)
{
    int* result = (int*)malloc(sizeof(int));
    *result = 20;
    for(int i=0; i<5; i++)
    {
       sleep(1);
       printf("My %d Turn \n",i);
    }
    return result;
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

    // create a NULL ptr used for recieving result
    void* result = NULL;
   // pass input value into thread
    pthread_create(&thread,NULL,myturn,NULL);
 
    yourturn();

    // wait for thread to finish and get the result
    //  we can also use a pointer to a pointer to get the result
    // pthread_join(pthread_t thread, void **retval);
    pthread_join(thread,&result);

    printf("Final result %d \n",*((int* )result));
    return 0;
}
