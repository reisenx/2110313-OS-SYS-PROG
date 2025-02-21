#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>

int main(int argc, char **argv) {
	int num_agents = 2;
	if(argc > 1)
		num_agents = atoi(argv[1]);
	printf("Starting a call center with %d agents.\n", num_agents);

	//
	// OS -- CRAETE NAMED SEMAPHORE HERE
	//

	int semval;
	while(1) {

		//
		// OS -- PLACE CURRENT VALUE OF SEMAPHORE IN 'semval' HERE
		//

		printf("There are %d agents available now.\n", semval);
		sleep(3);
	}
}

