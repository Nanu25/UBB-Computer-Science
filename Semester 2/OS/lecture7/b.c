#include "h.h"

int main(int argc, char **argv) {
	int shmid;
	struct absp* x;

	shmid = shmget(25, 0, 0);
	x = shmat(shmid, 0, 0);

	srand(time(NULL));
	while(1) {
		x->s = x->a + x-> b;
		x->p = x->a * x->b;
		
		if(x->p == x->s) {
			break;
		}

	}	

	shmdt(x);
	
	return 0
}
