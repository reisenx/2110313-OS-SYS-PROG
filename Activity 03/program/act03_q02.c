#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int compute_period = 5;
int sleep_period = 5;

/* what to do when alarm is on */
void on_alarm (int signal) {
	printf("Sleep\n");
	sleep(sleep_period);
	printf("Wake up\n");
	/* activate alarm again */
	alarm(compute_period);
}

int main() {
	/* Input from a keyboard instead of using arguments */
	printf("Enter compute period : \n");
	scanf("%d", &compute_period);
	printf("Enter sleep period : \n");
	scanf("%d", &sleep_period);

	/* on_alarm is signal handler for SINGLARM */
	signal(SIGALRM, on_alarm);
	/* activate alarm */
	alarm(compute_period);
	/* compute infinitely but can be interrupted by alarm */
	for(int i = 0; ;i++) {
		if(i == 0) printf("computing\n");
	}
	return 0;
}
