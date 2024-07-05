#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "fifo.h"

int main(int argc, char** argv) {
	int fd_write = open(myfifo11, O_WRONLY);
	int fd_read = open(myfifo22, O_RDONLY);

	if(fd_write < 0 || fd_read < 0) {
		printf("Error on open\n");
		exit(0);
	}

	char s[100];
	int lg;
	read(fd_read, &lg, sizeof(int));
	read(fd_read, s, sizeof(char) * lg);

	printf("Process B recived: %s \n", s);

	write(fd_write, s, sizeof(char) * lg);

	return 0;
}


