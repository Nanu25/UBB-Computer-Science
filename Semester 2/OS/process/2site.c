#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
	if(argc != 2) {
		printf("Invalid number of arguments\n");
		exit(0);
	}

	int n = atoi(argv[1]);
	for(int i = 0; i < n; i++) {
		int f = fork();
		if(f < 0) {
			printf("Error o fork");
			exit(1);
		}

		if(f == 0) {
			printf("Child id: %d, child pid: %d, parent pid: %d\n", i, getpid(), getppid());
		} else {
		
			 printf("Child pid: %d, parent pid: %d\n", f, getpid());
			 wait(0);
			 exit(0);
		}
	}

		
	return 0;

}
