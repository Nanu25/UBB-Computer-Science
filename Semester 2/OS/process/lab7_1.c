#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(int argc, char** argv) {
	if(argc < 0) {
		printf("Invalid number of arguments");
		exit(0);
	}

	if(execvp(argv[1], argv + 1) == 1) {
		printf("Error on execution\n");
		exit(0);
	}


	return 0;
}

