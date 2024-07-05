#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char** argv) {

	int a2b = open("./a2b", O_RDONLY);
	int b2a = open("./b2a", O_WRONLY);
	
	if(a2b < 0) {
		printf("Error on open file\n");
		exit(0);
	}

	if(b2a < 0) {
		printf("Error on open file\n");
		exit(0);
	}

	int n;
	if(read(a2b, &n, sizeof(int)) < 0){
                perror("Error on read\n");
                exit(0);
        }
	
	printf("B recived: %d\n", n);
	n = 100;
	if(write(b2a, &n, sizeof(n)) < 0) {

	}

	close(a2b);
	close(b2a);

	return 0;
}
