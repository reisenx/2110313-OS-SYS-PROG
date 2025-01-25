#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {
	int pid1, pid2;

	pid1 = fork();
	if(pid1 == 0) {
		// Child Process
		printf("I am the child process. My PID is %d ", getpid());
		printf("and my parent's PID is %d\n", getppid());

		pid2 = fork();
		if(pid2 == 0) {
			// Grandchild Process
			printf("I am the grandchild process. My PID is %d ", getpid());
			printf("and my parent's PID is %d\n", getppid());
		}
		else {
			waitpid(pid2, NULL, 0); // Child waits for its grandchild
		}
	}
	else {
		// Parent Process
		printf("I am the parent process. My PID is %d\n", getpid());
		waitpid(pid1, NULL, 0); // Parent waits for its child
	}
	return 0;
}
