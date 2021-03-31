#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void func1(int arg)
{
    int i;
    printf("func1: arg=%d\n", arg);
    for (i = 0; i < 10; ++i)
    {
        printf("func1 loop: i=%d\n", i);
    }
}

void func2(int arg)
{
    int i;
    printf("func2: arg=%d\n", arg);
    for (i = 0; i < 10; ++i)
    {
        printf("func2 loop: i=%d\n", i);
    }
}

int main()
{
    int arg1, arg2;
    pthread_t tid1, tid2;
    arg1 = 233;
    arg2 = 666;
    if(pthread_create(&tid1, NULL, (void *)func1, (void *)arg1))
    {
        printf("thread1 NOT created\n");
        exit(-1);
    }
    if (pthread_create(&tid2, NULL, (void *)func2, (void *)arg2))
    {
        printf("thread2 NOT created\n");
        exit(-1);
    }

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    printf("main thread run away\n");
    return 0;
}
