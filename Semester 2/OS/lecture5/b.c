#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
	int a[4] = {1, 2, 3, 4};
	
//This is make a copy in memory and don t affect the current process.	
	if(fork()==0) {
		a[2] += a[3];
		exit(0);
	}

	/*
	if(fork() == 0) {
	if(execlp("cat", "dog", NULL)==-1) {
		perror("something went bad");
		exit(0);	
	}
       	}
	*/
//	printf("we echoed!\n");
//
//
	a[0] += a[1];
	wait(0);
	a[0] += a[2];
	printf("%d\n", a[0]);


//	wait(0);
	return 0;
}
