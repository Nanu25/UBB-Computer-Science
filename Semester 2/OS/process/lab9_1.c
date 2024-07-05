#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char ** argv) {
	if(argc != 2) {
		printf("Invalid number of parameters\n");
		exit(0);
	}
	char sir[100];
	strcpy(sir, argv[1]);
	printf("The initial strig: %s\n", sir);
	char voc[] = "aeiouAEIOU";

	for(int i = 0; i < strlen(voc); i++) {
		int pd[2];

		if(pipe(pd) == -1) {
			printf("Error on pipe\n");
			exit(0);
		}

		int f = fork();
		if(f < 0) {
			printf("Error on fork\n");
			exit(0);
		}

		if(f == 0) {
			//child process
			
			close(pd[0]);	//children don t read

			char *temp = malloc(100 * sizeof(char));
			int k = 0;
			for(int j = 0; j < strlen(sir); j++) {
				if(sir[j] != voc[i])
					temp[k++] = sir[j];
			}
			temp[k] = '\0';
			write(pd[1], temp, 100);
			close(pd[1]);
			free(temp);
			exit(0);
		}

		close(pd[1]);
		read(pd[0], sir, 100);
		close(pd[0]);
		wait(0);

	}
	
	printf("The final string is: %s\n", sir);

	return 0;
}
