#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char** argv) {
	if(argc < 2) {
		printf("Invalid number of parameters\n");
		exit(1);
	}

	int n = atoi(argv[1]);
	for(int i = 0; i < n; i++) {
		int f = fork();
		if(f < 0) {
			printf("Error on fork\n");
		}
		else if(f == 0) {
			printf("Child pid: %d and parrent pid: %d\n", getpid(), getppid());
			exit(0);
		}else {
			printf("Child pid: %d and parrent pid %d\n", f, getpid());
		}
	}
	
	for(int i = 0; i < n; i++)
		wait(NULL);

	return 0;
}
