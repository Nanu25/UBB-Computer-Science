#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
	int a_b[2], b_a[2];
	if(pipe(a_b) < 0) {
		printf("Error on pipe\n");
		exit(0);
	}

       	if(pipe(b_a) < 0) {
                printf("Error on pipe\n");
                exit(0);
        }

	int f = fork();
	if(f < 0) {
		printf("Error on fork\n");
		exit(0);
	}
	
	//Child A
	if(f == 0) {
		close(a_b[1]);
		close(b_a[0]);
		int n;
		while(1) {
			if(read(a_b[0], &n, sizeof(int)) < 0) {
				printf("Error on read\n");
				exit(0);
			}
			n = n / 2;
			printf("Child send: %d \n", n);
			if(write(b_a[1], &n, sizeof(int)) < 0) {
				printf("Error on write\n");
				exit(0);
			}


			if(n <= 5)
				break;
		}

		close(a_b[0]);
		close(b_a[1]);
		exit(0);
	}
	
	close(a_b[0]);
	close(b_a[1]);
	
	srandom(getpid());
	int n = random() % 150 + 50;
	while(1) {
        	if(n % 2 == 1)
                	n++;

		printf("Parent send: %d \n", n);

		if(write(a_b[1], &n, sizeof(int)) < 0) {
			printf("Error on write\n");
			exit(0);
		}

		if(read(b_a[0], &n, sizeof(int)) < 0) {
			printf("Error on read\n");
			exit(0);
		}

		if(n <= 5) {
			printf("We obtain: %d \n", n);
			break;
		}
	}

	close(a_b[1]);
	close(b_a[0]);
	wait(0);
	return 0; 
}
