#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char** argv) {
	int a2b[2], b2a[2];

	if(pipe(a2b) < 0) {
		printf("Error on pipe\n");
		exit(0);
	}

       if(pipe(b2a) < 0) {
                printf("Error on pipe\n");
                exit(0);
        }


	int f = fork();
	if(f < 0) {
		printf("Error on fork\n");
		exit(0);
	}

	if(f == 0) {
		close(a2b[0]);
		close(b2a[1]);
		
		srandom(getpid());
		int b = random() % 900;
		b += 100;
		
		printf("B generates: %d \n", b);
		while(1) {
               		int a;
                	if(read(b2a[0], &a, sizeof(int)) < 0) {
                        	printf("Error on read\n");
                        	exit(0);
                	}
			
			int dif;
			if(a > b)
				dif = a - b;
			else dif = b - a;
			
			printf("B recived: %d and the diference if %d \n", a, dif);

			if(write(a2b[1], &dif, sizeof(int)) < 0) {
				printf("Error on write\n");
				exit(0);
			}

			if(dif <= 50)
				break;
		}

		close(a2b[1]);
		close(b2a[0]);
		exit(0);
	
	}
	close(a2b[1]);
	close(b2a[0]);
	srandom(getpid());
	int a, nr = 0;
	while(1) {
		a = random() % 950 + 100;
		if(write(b2a[1], &a, sizeof(int)) < 0) {
			printf("Error on write\n");
			exit(0);
		}

		int dif;
		nr++;
		if(read(a2b[0], &dif, sizeof(int)) < 0) {
                    printf("Error on read\n");
                    exit(0);
		}

		if(dif <= 50)
			break;
	}

	printf("Process A generated %d numbers\n", nr);
	close(a2b[0]);
	close(b2a[1]);
	wait(0);

	return 0;
}
