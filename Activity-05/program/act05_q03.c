#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void* print_message(void* data) {
    char* message = (char*) data;
    printf("%s\n", message);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pid_t pid = fork();
    // Child process
    if(pid == 0) {
        // Create 2 threads
        pthread_create(&t1, NULL, print_message, "First thread from child process");
        pthread_create(&t2, NULL, print_message, "Second thread from child process");
    }
    // Parent process
    else if(pid > 0) {
        // Create 2 threads
        pthread_create(&t1, NULL, print_message, "First thread from parent process");
        pthread_create(&t2, NULL, print_message, "Second thread from parent process");
    }
    // Error
    else {
        perror("Fork failed.");
        exit(1);
    }
    // The main thread wait until the t1 or t2 completes
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}