#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv) {
	int a2b = open("./a2b", O_RDONLY);
	if(-1 == a2b) {
        	perror("Error on opening fifo a2b");
        	exit(1);
   	}

	int b2a = open("./b2a", O_WRONLY);
        if(-1 == b2a) {
                perror("Error on opening fifo b2a");
                exit(1);
        }

	int nr;
	read(a2b, &nr, sizeof(int));
	nr += 5;
	write(b2a, &nr, sizeof(int));

	printf("The new number is: %d \n", nr);

	return 0;
}
