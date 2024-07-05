#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
int main(int argc, char **argv) {
	if(argc != 2) {
		printf("Invalid number of arguments\n");
		exit(0);
	}

	int n = atoi(argv[1]);
	
	int number[100];
	srandom(time(0));
	for(int i = 0; i < n; i++) {
		number[i] = random() % 100;
		printf("%d ", number[i]);
	}
	printf("\n");

	int p2c[2], c2p[2];
	if(pipe(p2c) == -1) {
		printf("Error on pipe\n");
		exit(0);
	}

	if(pipe(c2p) == -1) {
                printf("Error on pipe\n");
                exit(0);
        }

	int f = fork();

	if(f < 0) {
		printf("Error on fork\n");
		exit(0);
	}

	if(f == 0) {
		close(p2c[1]);
		close(c2p[0]);
		float rez = 0;
		for(int i = 0; i < n; i++) {
			int x;
			if(read(p2c[0], &x, sizeof(int)) < 0) {
				printf("Error on read\n");
				exit(0);
			}

			rez += x;
		}

		rez = rez / n;
		write(c2p[1], &rez, sizeof(float));
	       	close(p2c[0]);
       		close(c2p[1]);
 		exit(0);		
	}

	//Parent process
	close(p2c[0]);
	close(c2p[1]);

	for(int i = 0; i < n; i++) {
		write(p2c[1], &number[i], sizeof(int));
	}

	float rez;
	read(c2p[0], &rez, sizeof(float));
	printf("The result is: %f \n", rez);


	close(p2c[1]);
	close(c2p[0]);
	exit(0);

	return 0;
}
