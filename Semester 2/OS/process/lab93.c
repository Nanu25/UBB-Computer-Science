#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char **argv) {
	char text[] = "aa bbbbcc d";

	for(char i = 'a'; i <= 'z'; i++) {
		int pd[2];
		if(pipe(pd) == -1) {
			printf("Error on pipe\n");
			exit(0);
		}

		int f = fork();
		if (f < 0) {
			printf("Error on fork\n");
			exit(0);
		}

		if(f == 0) {
			close(pd[0]);
			int nr = 0;
			for(int j = 0; j < strlen(text); j++) 
				if(text[j] == i)
					nr++;
			write(pd[1], &nr, sizeof(int));
			close(pd[1]);
			exit(0);
		}


		close(pd[1]);

		int ap;
		read(pd[0], &ap, sizeof(int));
		if(ap != 0)
			printf("The letter %c appears %d times\n", i, ap);
		close(pd[0]);
		wait(0);
	}

	return 0;
}



