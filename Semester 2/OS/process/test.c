#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv) {

	int a2b[2], b2a[2];
	if(pipe(a2b) < 0) {
		perror("Error on open pipe\n");
		exit(0);
	}
        if(pipe(b2a) < 0) {
                perror("Error on open pipe\n");
                exit(0);
        }

	int f = fork();
	if(f < 0) {
	        perror("Error on open pipe\n");
                exit(0);
	}

	if(f == 0) {
		close(a2b[1]);
		close(b2a[0]);
		
		int n;
		if(read(a2b[0], &n, sizeof(int)) < 0) {
			perror("Error on read\n");
			exit(0);
		}
		
		int lg;
                if(read(a2b[0], &lg, sizeof(int)) < 0) {
                        perror("Error on read\n");
                        exit(0);
                }

		char nume[100];
               	if(read(a2b[0], nume, sizeof(char) * lg) < 0) {
                        perror("Error on read\n");
                        exit(0);
                }
		printf("Number n is: %d\n", n);
		printf("File name is: %s\n", nume);

		int nr = 0;
		char word[100][100];
		int k = 0;
		while(1) {
			if(read(a2b[0], &lg, sizeof(int)) < 0) {
				
			}
			if(lg == 0)
				break;
			read(a2b[0], word[k++], sizeof(char) * lg);

			if(lg == n)
				nr++;

		}

		printf("The number of words with n letters: %d\n", nr);
		
		if(nr % 2 == 0) {
			printf("Tell a word of %d letters: \n", n);
			char cuvant[100];
			scanf("%s", cuvant);
			
			FILE* file = fopen(nume, "w");
			fprintf(file, "%s ", cuvant);
			for(int i = 0; i < k; i++)
				fprintf(file, "%s ", word[i]);
		}

		close(a2b[0]);
		close(b2a[1]);
		exit(0);
	}

	close(a2b[0]);
	close(b2a[1]);

	printf("Tell the number n\n");
	int n;
	scanf("%d", &n);

	
	printf("Tell the name of the file\n");
	char name[100];
	scanf("%s", name);

	if(write(a2b[1], &n, sizeof(int)) < 0) {
		perror("Error on write\n");
		exit(0);
	}

	int lg = strlen(name);
	write(a2b[1], &lg, sizeof(int));
	if(write(a2b[1], name, sizeof(char) * lg) < 0) {
                perror("Error on write\n");
                exit(0);
        }


	FILE* file = fopen(name, "rw");
	char word[100];	
	while(fscanf(file, "%s", word) != EOF) {
		lg = strlen(word);
		write(a2b[1], &lg, sizeof(int));
		write(a2b[1], word, sizeof(char) * lg);

	}
	lg = 0;
	write(a2b[1], &lg, sizeof(int));
	fclose(file);
	close(a2b[1]);
	close(b2a[0]);
	wait(0);

	return 0;
}
