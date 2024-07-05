#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
int main(int argc, char** argv) {
        
	int a2b = open("./a2b", O_RDONLY);
	int b2a = open("./b2a", O_WRONLY);
	if(b2a < 0) {
                perror("Error on open b2a\n");
                exit(0);
        }

	char sir[105];
	int lg;
	lg = read(a2b, sir, 100 * sizeof(char));
	if(lg < 0) {
                perror("Error on read\n");
                exit(0);
	}

	for(int i = 0; i < lg; i++)
		sir[i] -= 32;

	if(write(b2a, sir, lg * sizeof(char)) < 0) {
                perror("Error on read\n");
                exit(0);
	}

	close(a2b);
	close(b2a);

	return 0;
}
