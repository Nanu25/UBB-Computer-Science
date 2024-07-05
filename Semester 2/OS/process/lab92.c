#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
	if(argc != 2) {
		printf("Invalid number of paratemers\n");
		exit(0);
	}

	int n = atoi(argv[1]);

	int *number = malloc(n * sizeof(int));
	for(int i = 0; i < n; i++) {
		number[i] = i + 1;
	}

	for(int i = 2; i <= n; i++) {

		int f = fork();
		if(f < 0) {
			printf("Error on fork\n");
			exit(0);
		}

		if(f == 0) {
			FILE* fd = fopen("numere.txt", "r");
			if(fd == NULL) {
				printf("Error on opening\n");
				exit(0);
			}

			int *temp = malloc(n * sizeof(int));
			int k = 0;
			int x;
			while(fscanf(fd, "%d", &x) > 0) {
				if(x % i != 0 || x == i)
					temp[k++] = x;
			}

			fclose(fd);

			fd = fopen("numere.txt", "w");
                        if(fd == NULL) {
                                printf("Error on opening\n");
                                exit(0);
                        }

			for(int j = 0; j < k; j++)
				fprintf(fd, "%d ", temp[j]);
			fclose(fd);
			free(temp);
		}

		wait(0);

	}



	return 0;
}
