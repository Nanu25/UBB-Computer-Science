#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

//Print n even numbers and n odd numbers not overlapping.

typedef struct {
	int n;
} data;

pthread_mutex_t ma, mb;

void* feven(void *a) {
	data b = *((data*) a);
	while(b.n != 0) {
		pthread_mutex_lock(&ma);
		int x = random() % 100;
		if(x % 2 == 1)
			x++;

		printf("%d\n", x);
	       	b.n--;	
		pthread_mutex_unlock(&mb);
		
	}
	return NULL;
}

void *fodd(void *a) {
        data b = *((data*) a);
        while(b.n != 0) {
        	pthread_mutex_lock(&mb);
		int x = random() % 100;
                if(x % 2 == 0)
                        x++;

                printf("%d\n", x);
                b.n--;

        	pthread_mutex_unlock(&ma);
	}

	return NULL;
}

int main(int argc, char **argv) {
	pthread_t t1, t2;
	srandom(getpid());
	data x, y;
	x.n = 10;
	y.n = 10;
	pthread_mutex_init(&ma, NULL);
	pthread_mutex_init(&mb, NULL);
	pthread_mutex_lock(&mb);

	pthread_create(&t1, NULL, feven, &x);
	pthread_create(&t2, NULL, fodd, &y);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	

	return 0;
}
