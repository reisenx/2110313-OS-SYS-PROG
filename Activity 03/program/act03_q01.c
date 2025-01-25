#include<stdio.h>

int main() {
	int pid1, pid2;

	pid1 = fork();
	if(pid1 == 0) {
		printf("I am the child process. My PID is %d ", getpid());
		printf("and my parent's PID is %d\n", getppid());

		pid2 = fork();
		if(pid2 == 0) {
			printf("I am the grandchild process. My PID is %d ", getpid());
			printf("and my parent's PID is %d\n", getppid());
		}
	}
	else {
		printf("I am the parent process. My PID is %d\n", getpid());
	}
	return 0;
}
