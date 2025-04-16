#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main() {
	int n = 4;
	pid_t childpid;

	for(int i = 0; i < n; ++i) {
		childpid = fork();
		// Parent process
		if(childpid > 0) {
			break;
		}
	}

	// Parent waits for its child to finish
	wait(0);
	printf("This process %ld ", (long) getpid());
	printf("with parent %ld \n", (long) getppid());
	return 0;
}
