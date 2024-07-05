#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
	if(mkfifo("./a2b", 0600) < 0) {
		perror("Error on make fifo1\n");
		exit(0);
	}
	

        if(mkfifo("./b2a", 0600) < 0) {
                perror("Error on make fifo1\n");
                exit(0);
        }

	int a2b = open("./a2b", O_WRONLY);
	int b2a = open("./b2a", O_RDONLY);
	
	if(a2b < 0) {
		printf("Error on open file\n");
		exit(0);
	}

	if(b2a < 0) {
		printf("Error on open file\n");
		exit(0);
	}

	int n;
	printf("Tell the number\n");
	scanf("%d", &n);

	if(write(a2b, &n, sizeof(int)) < 0) {
                perror("Error on write\n");
                exit(0);
        }
	
	read(b2a, &n, sizeof(int));
	printf("New n %d\n", n);

	close(a2b);
	close(b2a);
	unlink("./a2b");
	unlink("./b2a");

	return 0;
}
