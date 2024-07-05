/*
21. Write a C program that creates 2^N threads that race to the finish (N is a command line argument). The threads must pass through N checkpoint. The checkpoint with number X will allow half as many threads to pass simultaneously than checkpoint number X - 1 (N >= X >=1). Checkpoint 0 (the first one) will allow 2^(N-1) to pass simultaneously through it.*/

#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
	int id;
}data;

pthread_barrier_t b;
sem_t sem[1024];
int n;

void *fa(void *a) {
	data* d = (data*)a;

	printf("Thread %d started\n", d->id);
	
	pthread_barrier_wait(&b);

	for(int i = 0; i < n; i++) {
		sem_wait(&sem[i]);

		printf("Thread %d entered checkpoint %d\n", d->id, i);
		usleep(1000);
		printf("Thread %d left checkpoint %d\n", d->id, i);
		sem_post(&sem[i]);
	}
	
	printf("Thread %d finished\n", d->id);
	return NULL;
}

int main(int argc, char** argv) {
	if(argc != 2) {
		perror("Please insert one argument\n");
		exit(0);
	}

	n = atoi(argv[1]);
	int nrt = 1;
	for(int i = 0; i < n; i++)
		nrt *= 2;
	
	int step = 1;
	for(int i = 0; i < n; i++) {
		sem_init(&sem[i], 0, nrt / step);
		step *= 2;
	}	

	pthread_barrier_init(&b, NULL, nrt);
	pthread_t *th = malloc(sizeof(pthread_t) * nrt);
	data *d = malloc(sizeof(data) * nrt);

	for(int i = 0; i < nrt; i++) {
		d[i].id = i;
		if(pthread_create(&th[i], NULL, fa, &d[i]) < 0) {
			perror("Unable to create thread\n");
			exit(1);
		}
	}

	for(int i = 0; i < nrt; i++)
		pthread_join(th[i], NULL);

	free(th);	
	free(d);
	pthread_barrier_destroy(&b);
	for(int i = 0; i < n; i++)
		sem_destroy(&sem[i]);
	
	return 0;
}



