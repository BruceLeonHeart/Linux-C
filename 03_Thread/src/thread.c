#include <pthread.h>
#include <unistd.h> //man 3 sleep
#include <stdio.h>

void* myturn(void* args)
{
    for(int i=0; i<20; i++)
    {
       sleep(1);
       printf("My %d Turn \n",i);
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

    /*
        #include <pthread.h>

        int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                            void *(*start_routine) (void *), void *arg);

        Compile and link with -pthread.
    */
    pthread_create(&thread,NULL,myturn,NULL);
 
    yourturn();

    pthread_join(thread,NULL);

    return 0;
}
