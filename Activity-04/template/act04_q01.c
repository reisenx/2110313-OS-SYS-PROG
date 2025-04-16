#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {
	pid_t pid;
	char *av[] = {"cal", "3", "2021", (char *)0};

    pid = fork();
    if(pid < 0) {
        printf("Error : cannot fork\n");
        exit(1);
    }
    else if(pid == 0) {
        execvp("cal", av);
    }
    else {
        wait(NULL);
        return 0;
    }
}
