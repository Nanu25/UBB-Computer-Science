
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
	int p2g[2], g2a[2];

	pipe(p2g);
	pipe(g2a);
	if(fork() == 0) {
		close(g2a[0]);
		close(g2a[1]);
		close(p2g[0]);
		dup2(p2g[1], 1);
		execlp("ps", "ps", "-ef", NULL);
		exit(0);
	}

       if(fork() == 0) {
                close(g2a[0]);
                close(p2g[1]);
                dup2(p2g[0], 0);
		dup2(g2a[1], 1);
                execlp("grep","grep", "-E", "^root", NULL);
                exit(0);
        }

		        if(fork() == 0) {
                close(p2g[0]);
                close(g2a[1]);
                close(p2g[1]);
                dup2(g2a[0], 0);
                execlp("awk", "awk", "{print $2}", NULL);
                exit(0);
        }

	close(p2g[0]);
	close(p2g[1]);
	close(g2a[0]);
	close(g2a[1]);
	wait(0);
	wait(0);
	wait(0);


	return 0;
}
