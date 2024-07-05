#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int f;

void child_handler(int sig) {
	printf("Child process is over\n");
	exit(0);
}

void parent_handler(int sig) {
	printf("Parent procecss is over\n");
	kill(f, SIGUSR1);
	wait(0);
	exit(0);
}

void zombie_handler(int sig) {
	printf("Waiting for child process to finish\n");
	exit(0);
}

int main(int argc, char** argv) {
	f = fork();
	if(f < 0) {
		printf("Error on fork\n");
		exit(0);
	}

	if(f == 0) {
		signal(SIGUSR1, child_handler);
 		printf("C - Child PID: %d Parent PID: %d\n", getpid(),getppid());		
		while(1) {
			printf("Child procecss is working...\n");
			sleep(3);
		}
		exit(0);
	}else {
		signal(SIGUSR1, parent_handler);
		signal(SIGCHLD, zombie_handler);
		printf("P - Child PID: %d Parent PID: %d\n", f, getpid());
		while(1) {
			printf("Parent process is working\n");
			sleep(3);
		}
	}
	

	return 0;
}

