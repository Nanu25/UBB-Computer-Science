#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
	int id;
}data;

int stop = 0;
pthread_barrier_t b;
pthread_mutex_t m;

void *fa(void *a) {
	data *d = (data*) a;
	int i = d->id;

	printf("Thread %d started\n", i);
	pthread_barrier_wait(&b);		//we wait all the threads to start.

	printf("All thread started\n");
	
	int x;
	while(1) {
		pthread_mutex_lock(&m);
		if(stop == 1)
			break;
		x = rand() % 111111;
		if(x % 1001 == 0) {
			stop = 1;
			printf("Thread %d generates %d\n", i, x);
			break;
		}
		printf("Thread %d generates %d\n", i, x);
		pthread_mutex_unlock(&m);
	}
	pthread_mutex_unlock(&m);

	return NULL;
}

int main(int argc, char** argv) {
	if(argc != 2) {
		printf("Please insert one argument!");
		exit(0);
	}

	srandom(getpid());
	int n = atoi(argv[1]);

	pthread_barrier_init(&b, NULL, n);
	pthread_mutex_init(&m, NULL);

	pthread_t *th = malloc(sizeof(pthread_t) * n);
	for(int i = 0; i < n; i++) {
		data *d = malloc(sizeof(data));
		d->id = i;
		if(pthread_create(&th[i], NULL, fa, d) < 0) {
			perror("Unable to create thread\n");
			exit(1);
		}
	}

	for(int i = 0; i < n; i++)
		pthread_join(th[i], NULL);

	free(th);
	pthread_barrier_destroy(&b);
	pthread_mutex_destroy(&m);

	return 0;
}
