#include<stdio.h>
#include<pthread.h>

// Set the amount of thread here.
#define AMOUNT 10
void* print_number(void* data) {
    int thread_num = *((int*) data);
    printf("This is thread %d\n", thread_num);
    return NULL;
}

int main() {
    // Create 10 threads
    pthread_t threads[AMOUNT];
    for(int i = 0; i < AMOUNT; i++) {
        // Runs print_number(i+1)
        pthread_create(&threads[i], NULL, print_number, i+1);
    }
    
    // The main thread wait until the all 10 threads completes
    for(int i = 0; i < AMOUNT; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}