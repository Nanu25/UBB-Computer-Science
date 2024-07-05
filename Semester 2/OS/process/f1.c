#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
	if(mkfifo("./a2b",  0600) < 0) {
		perror("Error on fifo\n");
		exit(0);
	}


	if(mkfifo("./b2a", 0600) < 0) {
	        perror("Error on fifo\n");
                exit(0);
        }


	int a2b = open("./a2b", O_WRONLY);
	if(-1 == a2b) {
        	perror("Error on opening fifo a2b");
        	exit(1);
   	}

	int b2a = open("./b2a", O_RDONLY);
        if(-1 == b2a) {
                perror("Error on opening fifo b2a");
                exit(1);
        }

	int nr = 10;
	write(a2b, &nr, sizeof(int));
	read(b2a, &nr, sizeof(int));

	printf("The new number is: %d \n", nr);
	unlink("./a2b");
	unlink("./b2a");

	return 0;
}
