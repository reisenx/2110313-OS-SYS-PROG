#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

/* argc is argument count
   *argv[] is argument vector */
int main(int argc, char *argv[]) {
	pid_t pid;
	// Has input command (argument count > 1)
	if(argc > 1) {
		pid = fork();
		if(pid < 0) {
			printf("Error : cannot fork\n");
			exit(1);
		}
		else if(pid == 0) {
			// Execute the input UNIX command
			execvp(argv[1], &argv[1]);
		}
		else wait(NULL); // Parent waits for its child.
	}
	else {
		printf("Please enter UNIX command.\n");
	}
	return 0;
}
