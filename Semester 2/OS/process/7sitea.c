#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "header.h"
int main(int argc, char **argv) {
	if (0 > mkfifo(myfifo1, 0600)) {
    		perror("Error on make fifo 1\n");
    		exit(1);
  	}
  	if (0 > mkfifo(myfifo2, 0600)) {
    		perror("Error on make fifo 2\n");
    		exit(1);
  	}

	int fd_write = open(myfifo1, O_WRONLY);
	if(fd_write == -1) {
		printf("Error on write fifo\n");
		exit(0);
	}

	int fd_read = open(myfifo2, O_RDONLY);
       	if(fd_write == -1) {
                printf("Error on read fifo\n");
                exit(0);
        }

	printf("Here 1\n");	
	srandom(getpid());
	int nr = 0;
	while(nr != 10) {
		nr = random() % 11;
		printf("Parent sends: %d \n", nr);

		write(fd_write, &nr, sizeof(int));

		read(fd_read, &nr, sizeof(int));
		printf("Paernt recived: %d \n", nr);
	}
	
	close(fd_write);
  	close(fd_read);
  	
	if(0 > unlink(myfifo1)) {
    		perror("Error removing fifo 1");
  	}
  	if(0 > unlink(myfifo2)) {
    		perror("Error removing fifo 2");
  	}
	

	return 0;
}
