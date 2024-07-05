#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char** argv) {
	if(mkfifo("./a2b", 0600) < 0) {
		perror("Error on make fifo\n");
		exit(0);
	}
        
	if(mkfifo("./b2a", 0600) < 0) {
                perror("Error on make fifo\n");
                exit(0);
        }

	int a2b = open("./a2b", O_WRONLY);
	if(a2b < 0) {
		perror("Error on open a2b\n");
		exit(0);
	}

	int b2a = open("./b2a", O_RDONLY);
	if(b2a < 0) {
                perror("Error on open b2a\n");
                exit(0);
        }

	char sir[105];
	printf("Tell the string\n");
	scanf("%s", sir);
	int lg = strlen(sir);
	if(write(a2b, sir, lg * sizeof(char)) < 0) {
                perror("Error on read\n");
                exit(0);
	}

	if(read(b2a, sir, lg * sizeof(char)) < 0) {
                perror("Error on read\n");
                exit(0);
	}

	printf("The string: %s\n", sir);
	close(a2b);
	close(b2a);
	unlink("./a2b");
	unlink("./b2a");

	return 0;
}
