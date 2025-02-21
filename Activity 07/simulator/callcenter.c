#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>

#define SEM_NAME "callcenter"

int main(int argc, char **argv) {
	int num_agents = 2;
	if(argc > 1)
		num_agents = atoi(argv[1]);
	printf("Starting a call center with %d agents.\n", num_agents);

	// OS -- CREATE NAMED SEMAPHORE HERE
	sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0644, num_agents);
	int semval;
	while(1) {
		// OS -- PLACE CURRENT VALUE OF SEMAPHORE IN 'semval' HERE
		sem_getvalue(sem, &semval);
		printf("There are %d agents available now.\n", semval);
		sleep(3);
	}
	// Close the semaphore when finished
	sem_close(sem);
	return 0;
}
