#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
/*
model2: Se fac 2 procese, unul din ele genereaza random un n si citeste de la tastatura un k, 
le trimite prin pipe la celalalt proces. Al doilea proces, daca k e par face suma cifrelor lui n, altfel 
face produsul cifrelor lui n si scrie in fisier rezultatul obtinut.
*/
int main(int argc, char** argv) {
	int p2c[2], c2p[2];

	if(pipe(p2c) < 0) {
		perror("Error on make pipo\n");
		exit(0);
	}
  	if(pipe(c2p) < 0) {
                perror("Error on make pipo\n");
                exit(0);
        }

	int f = fork();
	if(f < 0) {
                perror("Error on make fork\n");
                exit(0);
        }

	if(f == 0) {
		close(p2c[1]);
		close(c2p[0]);

		int n, k;
		if(read(p2c[0], &n, sizeof(int)) < 0) {
			perror("Error on read\n");
			exit(0);
		}

		if(read(p2c[0], &k, sizeof(int)) < 0) {
                	perror("Error on read\n");
                	exit(0);
        	}

		printf("Process B recived %d\n", n);
		int nr = 0;
		if(k % 2 == 0) {
			while(n) {
				nr += n % 10;
				n /= 10;
			}
		}else {
			nr = 1;
			while(n) {
				nr *= n % 10;
				n /= 10;
			}
		}
		
		FILE* file= fopen("aa.txt", "w");
		fprintf(file, "%d", nr);


		close(p2c[0]);
		close(c2p[1]);
		exit(0);
	}

	close(p2c[0]);
	close(c2p[1]);

	srandom(getpid());
	int n = random() % 100;
	int k;
	printf("Tell the number k: \n");
	scanf("%d", &k);

	write(p2c[1], &n, sizeof(int));
	write(p2c[1], &k, sizeof(int));
	wait(0);

	return 0;
}

