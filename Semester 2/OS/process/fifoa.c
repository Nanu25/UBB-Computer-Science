#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "fifo.h"

int main(int argc, char** argv) {
	if(mkfifo(myfifo11, 0600) < 0) {
		perror("Error on make fifo1\n");
		exit(0);
	}
	if(mkfifo(myfifo22, 0600) < 0) {
		printf("Error on make fifo2\n");
                exit(0);
        }

	int fd_write = open(myfifo11, O_WRONLY);
	if(fd_write < 0) {
		printf("Error on open\n");
		exit(0);
	}

	int fd_read = open(myfifo22, O_RDONLY);
      	if(fd_read < 0) {
                printf("Error on open\n");
                exit(0);
        }

	char s[100];
	printf("Tell a string %s \n", s);

	int lg = strlen(s);
	write(fd_write, &lg, sizeof(int));
	write(fd_write, s, sizeof(char) * lg);
	
	read(fd_read, s, sizeof(char) * lg);

	printf("Final string is: %s\n", s);

	return 0;

}
