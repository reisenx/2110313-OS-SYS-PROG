#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

main() {
	int i;
    int n;
	pid_t childpid;

    n = 4;
	for(i = 0; i < n; ++i) {
		childpid = fork();
		if(childpid > 0) {
			break;
		}
	}
	printf("This process %ld with parent %ld\n", (long) getpid(), (long) getppid());
	wait(0);
}
