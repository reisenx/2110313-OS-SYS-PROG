#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <semaphore.h>

int rand_int(int n)
{
	// Generate random integer number between [1, n]
	int r = rand();
	return (r % n) + 1;
}

int main(int argc, char **argv)
{
	printf("Starting customer\n");

	//
	// OS -- OPEN NAMED SEMAPHORE HERE
	//


	while (1)
	{
		// Customer will sleep between 1-3 seconds before placing the next phone call
		int sleep_time = rand_int(3);
		printf("Do something else for %d minutes\n\n", sleep_time);
		sleep(sleep_time);
		printf("Next customer calls the call center, press ten buttons, and listens to silly music.\n");
		time_t t0 = time(NULL);
		// Wait for an agent

		//
		// OS -- LOCK SEMAPHORE HERE
		//


		time_t t = time(NULL) - t0;
		// An agent accepts the call, using it for 3-5 seconds.
		int call_time = rand_int(3)+2;
		printf("After waiting for %ld minutes, an agent accepts the call.  Talk for %d minutes.\n", t, call_time);
		sleep(call_time);
		// Customer hangs up the phone

		//
		// OS -- UNLOCK SEMAPHORE HERE
		//


		printf("Customer ends the call.\n");
	}
}

