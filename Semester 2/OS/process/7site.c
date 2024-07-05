/*
 * Write a C program that creates two child processes. The two child processes will alternate sending random integers between 1 and 10 (inclusively) to one another until one of them sends the number 10. Print messages as the numbers are sent.
  */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
	int c1_c2[2], c2_c1[2];

	if(pipe(c1_c2) < 0) {
		printf("Error on pipe\n");
		exit(0);
	}

       	if(pipe(c2_c1) < 0) {
                printf("Error on pipe\n");
                exit(0);
        }

	int f = fork();
	if(f < 0) {
		printf("Error on fork\n");
		exit(0);
	}

	if(f == 0) {
		//first child;
		close(c1_c2[0]);	//nu am cum sa citesc cu c1 in c2.
		close(c2_c1[1]);	//nu am cum sa scriu pentru c2 in c2
		int nr = 0;
		if(read(c2_c1[0], &nr, sizeof(int)) < 0) {
			printf("Error on read\n");
			exit(0);
		}
		
		srandom(getpid());
		printf("Child recived: %d \n", nr);
		while(nr != 10) {
			nr = random() % 11;
			if(write(c1_c2[1], &nr, sizeof(int)) < 0) {
				printf("Error on write\n");
				exit(0);
			}

			if(nr == 10) {
				break;
			}

	                if(read(c2_c1[0], &nr, sizeof(int)) < 0) {
                        	printf("Error on read\n");
                        	exit(0);
                	}

			printf("Child recived: %d \n", nr);
		}

		close(c1_c2[1]);
		close(c2_c1[0]);
		exit(0);
	}

	f = fork();
	if(f < 0) {
		printf("Error on fork\n");
		exit(0);
	}

	if(f == 0) {
		close(c1_c2[1]);
		close(c2_c1[0]);

		int nr = 0;
		srandom(getpid());
		while(nr != 10) {
			nr = random() % 11;
			if(write(c2_c1[1], &nr, sizeof(int)) < 0) {
				printf("Error on write\n");
				exit(0);
			}

			if(nr == 10) {
				printf("Found value 10\n");
				break;
			}
			
			if(read(c1_c2[0], &nr, sizeof(int)) < 0) {
				printf("Error on read\n");
				break;
			}

			printf("Child 2 recived: %d \n", nr);
		}

		close(c1_c2[0]);
		close(c2_c1[1]);
		exit(0);
	}
	
	wait(0);
	wait(0);

	return 0;
}

