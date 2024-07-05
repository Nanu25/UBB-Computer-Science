#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
#include "header.h"
int main(int argc, char **argv) {


	int fd_write = open(myfifo1, O_WRONLY);
	int fd_read = open(myfifo2, O_RDONLY);
	
	srandom(getpid());
	int nr = 0;
	while(nr != 10) {
		nr = random() % 11;
		if(read(fd_read, &nr, sizeof(int)) < 0) {
			printf("Error on read\n");
			exit(0);
		}

		printf("B recived: %d \n", nr);
		if(write(fd_write, &nr, sizeof(int)) < 0) {
			printf("Error on write\n");
			exit(0);
		}

		printf("B sends: %d \n", nr);
	}

	close(fd_read);
	close(fd_write);

	return 0;
}
