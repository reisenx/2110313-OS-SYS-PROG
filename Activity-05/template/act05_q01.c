#include<stdio.h>
#include<pthread.h>

void* say_hello(void* data)
{
    char *str;
    str = (char*) data;
    while(1)
    {
        printf("%s\n", str);
        sleep(1);
    }
}

void main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, say_hello, "hello from 1");
    pthread_create(&t2, NULL, say_hello, "hello from 2");
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}