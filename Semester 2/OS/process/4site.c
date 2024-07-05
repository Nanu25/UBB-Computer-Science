#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
int main(int argc, char **argv) {
	struct timeval tv1, tv2;
	gettimeofday(&tv1, NULL);

	if(argc < 2) {
		printf("Invalid number of arguments\n");
		exit(0);
	}

	int f = fork();

	if(f < 0) {
		printf("Error on fork\n");
		exit(0);
	}


	if(f == 0) {
		if(execvp(argv[1], argv + 1) == -1) {
			printf("Error on execution\n");
			exit(0);
		}
		exit(0);
	}else {
		wait(0);
	        gettimeofday(&tv2, NULL);
        printf("Total time = %f seconds\n", (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
	}

	return 0;
}

