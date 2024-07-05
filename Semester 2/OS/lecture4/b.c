#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>


int main(int argc, char ** argv) {
	int pid;
	
	printf("before\n");
	pid = fork();	
	if(pid == 0) {
		printf("Child specific code pid=%d fork return = %d \n", getpid(), pid);
		exit(0);
	}
	printf("parent specific code child PID = %d\n", pid);
	wait(0);

	//fork returns 0 for the child.

        return 0;
}
