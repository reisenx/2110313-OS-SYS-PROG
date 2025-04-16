#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int tokenize(char *string, char *delimiters, char ***arrayOfTokens) {
	char *token;
	int numtokens = 0;
	/* skip the beginning delimiters */
	string += strspn(string, delimiters);
	if((token = malloc(strlen(string) + 1)) == NULL) {
		return -1;
	}

	/* count tokens */
	strcpy(token, string);
	if(strtok(token, delimiters) != NULL) {
		for(numtokens = 1; strtok(NULL, delimiters) != NULL; numtokens++);
	}

	/* create array of pointers to tokens */
	if((*arrayOfTokens = malloc((numtokens+1) * sizeof(char *))) == NULL) {
		free(token);
		return -1;
	}

	/* fill pointers to tokens into the array */
	if(numtokens == 0) free(token);
	else {
		strcpy(token, string);
		(*arrayOfTokens)[0] = strtok(token, delimiters);
		for(int i = 1; i < numtokens; i++) {
			(*arrayOfTokens)[i] = strtok(NULL, delimiters);
		}
		(*arrayOfTokens)[numtokens] = NULL;
	}
	return numtokens;
}

int main() {
	/* the program loops until exit */
	int run = 1;
	while(run) {
		printf("mysh >");
		/*  Variables declaration */
		char string[256];
		char **arrayOfTokens = NULL;
		char delimiters[] = " \t\n";

		/*  Input and tokenize to get array of arguments */
		fgets(string, 256, stdin);
		tokenize(string, delimiters, &arrayOfTokens);

		/*  Exit command */
		if(strcmp(arrayOfTokens[0], "exit") == 0) {
			run = 0;
		}
		/* Normal commands */
		else {
			pid_t pid;
			pid = fork();
			if(pid < 0) {
				printf("Error occurred.\n");
				exit(1);
			}
			else if(pid == 0) {
				/* Execute the command */
				execvp(arrayOfTokens[0], arrayOfTokens);
			}
			else {
				wait(NULL); // parents waits for its child.
			}
		}
		/* Free the allocated memory after execute in each loop */
		free(arrayOfTokens[0]);
		free(arrayOfTokens);
	}
	return 0;
}
