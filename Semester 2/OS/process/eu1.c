#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
//Convert all the lower cases to the uppercases.
//Create a process for each letter
int main(int argc, char ** argv) {
	char sir[100];
	printf("Tell the string you want to convert\n");
	scanf("%s", sir);

	printf("The initial string is: %s\n", sir);

	for(char j = 'a'; j <= 'z'; j++) {
		
		//i need to make pipes for every process.
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
			close(p2c[0]);
			close(c2p[1]);

			char newsir[100];
			int lg;
		 	if(read(c2p[0], &lg, sizeof(int)) < 0) {
                        	printf("Error on read\n");
                        	exit(0);
                	}
	
			if(read(c2p[0], &newsir, sizeof(char) * lg) < 0) {
				printf("Error on read\n");
				exit(0);
			}	

			for(int i = 0; i < lg; i++)
				if(newsir[i] == j)
					newsir[i] -= 32;

			if(write(p2c[1], newsir, sizeof(char) * lg) < 0) {
				printf("Error on write\n");
				exit(0);
			}	

		
			close(p2c[1]);
			close(c2p[0]);
			exit(0);
		
		}
	
		
        close(p2c[1]);
        close(c2p[0]);
        int lg = strlen(sir);
        if(write(c2p[1], &lg, sizeof(int)) < 0) {
                        printf("Error on write\n");
                        exit(0);
        }
        if(write(c2p[1], sir, sizeof(char) * strlen(sir)) < 0) {
                        printf("Error on write\n");
                        exit(0);
        }

        if(read(p2c[0], sir, sizeof(char) * strlen(sir)) < 0) {
               printf("Error on read\n");
                exit(0);
        }
	wait(0);
	}

	printf("The new string: %s \n", sir);
	return 0;
}
