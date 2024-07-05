#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
	int a[4] = {1, 2, 3, 4};
	int p[2];	
//This is make a copy in memory and don t affect the current process.	
	//Close pipe as soon as you don t need it anymore.
	//Read mode and write mode.
	
	pipe(p);
	if(fork()==0) {
		close(p[0]);
		a[2] += a[3];
		write(p[1], &a[2], sizeof(int));
		close(p[1]);
		exit(0);
	}
	close(p[1]);
	a[0] += a[1];
	read(p[0], &a[2], sizeof(int));
	close(p[0]);
	wait(0);

	a[0] += a[2];
	printf("%d\n", a[0]);


	return 0;
}
