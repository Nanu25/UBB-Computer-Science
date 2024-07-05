#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
//Sa se genereze aleator litere mari(65-90) in procesul A iar procesul B
//Trebuie sa verifice daca s-a obtinut litera A de 3 ori.

int main(int argc, char** argv) {
	int p2c[2], c2p[2];
	if(pipe(p2c) < 0) {
		printf("Error on pipe\n");
		exit(0);
	}

	if(pipe(c2p) < 0) {
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

		char ch;
		int nrA = 0;
		while(1) {
			if(read(p2c[0], &ch, sizeof(char)) < 0) {
				printf("Error on read\n");
				exit(0);
			}
			
			printf("Process B recived: %c \n", ch);

			if(ch == 'A')
				nrA++;

			if(write(c2p[1], &nrA, sizeof(int)) < 0) {
	                        printf("Error on write\n");
                                exit(0);
			}

			if(nrA == 3)
				break;
			
		}

		close(p2c[0]);
		close(c2p[1]);
		exit(0);
	}

	close(p2c[0]);
	close(c2p[1]);
	srandom(getpid());
	while(1) {
		char ch = random() % 31 + 60;
               	if(write(p2c[1], &ch, sizeof(char)) < 0) {
                	printf("Error on write\n");
               	        exit(0);
                }

		int nr;
               	if(read(c2p[0], &nr, sizeof(int)) < 0) {
                       printf("Error on read\n");
                       exit(0);
                }

		if(nr == 3)
			break;
	}

	printf("We got 3 A\n");
	close(p2c[1]);
	close(c2p[0]);
	wait(0);

	return 0;
}
