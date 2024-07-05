#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) {
	for(int i = 1; i < argc; i++) {
		int p2a[2], a2p[2];
		pipe(p2a);
		pipe(a2p);
		int f = fork();
		if(f == 0) {
			close(p2a[1]);
			close(a2p[0]);

			int lg;
			read(p2a[0], &lg, sizeof(int));
			char s[100];
			read(p2a[0], s, sizeof(char) * lg);

			printf("%s \n", s);

			close(p2a[0]);
			close(a2p[1]);
			exit(0);
		}

		close(p2a[0]);
		close(a2p[1]);
		int l = strlen(argv[i]);
		write(p2a[1], &l, sizeof(int));
		write(p2a[1], argv[i], sizeof(char) * l);

		close(p2a[1]);
		close(a2p[0]);
		wait(0);
		wait(0);
	}
	return 0;
}
