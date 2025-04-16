#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void* say_hello(void* data) {
    char *str;
    str = (char*) data;
    while(1) {
        printf("%s\n", str);
        sleep(1);
    }
    return NULL;
}

/* argc is argument count
   *argv[] is argument vector */
int main(int argc, char *argv[]) {
    // Check argument count
    if(argc != 3) {
        printf("usage: %s arg1 arg2\n", argv[0]);
    }

    // Create 2 threads
    pthread_t t1, t2;
    pthread_create(&t1, NULL, say_hello, argv[1]); // Runs say_hello(argv[1])
    pthread_create(&t2, NULL, say_hello, argv[2]); // Runs say_hello(argv[2])
    
    // The main thread wait until the t1 or t2 completes
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}