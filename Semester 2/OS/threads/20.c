#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

typedef struct{
	int id;
	int times;
}data;

pthread_mutex_t checkpoint = PTHREAD_MUTEX_INITIALIZER;
//or we can use a semaphore.
//sem_t checkpoint;
pthread_barrier_t b;

void *fthread(void *a) {
	data* d = (data*)a;
	printf("Thread %d started\n", d->id);
	
	
	int n = d->times;
	pthread_barrier_wait(&b);
	while(n--) {
		printf("Thread %d waiting on checkpoint %d\n", d->id, n);

		pthread_mutex_lock(&checkpoint);
		//sem_wait(&checkpoint);
		
		int entered = 0;
		int i = 0;
			
		usleep(rand() % 2 * 100000 + 100000);
		entered = 1;
		pthread_mutex_unlock(&checkpoint);
	}

	printf("Thread %d done\n", d->id);
	free(a);
	return NULL;
}

int main(int argc, char** argv) {
	if(argc != 3) {
		printf("Usage: n, m\n");
		exit(0);
	}

	pthread_t *th;
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);
	printf("N: %d, M: %d\n", n, m);


	pthread_barrier_init(&b, NULL, n);
	//sem_init(&checkpoint, 0, 1);

	th = (pthread_t*)malloc(sizeof(pthread_t) * n);
	for(int i = 0; i < n; i++) {
		data* d = (data*)malloc(sizeof(data));
		d->id = i;
		d->times = m;
		if(pthread_create(&th[i], NULL, fthread, d) < 0) {
			perror("Error on creating thread\n");
			exit(2);
		}
	}

	for(int i = 0; i < n; i++) {
		pthread_join(th[i], NULL);
	}

	free(th);
	pthread_barrier_destroy(&b);
	pthread_mutex_destroy(&checkpoint);
	//sem_destroy(&checkpoint);
	
	return 0;
}
