#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
typedef struct {
	int id;
}data;

int n, m;
sem_t sems[30];
pthread_barrier_t barrier;

void *fa(void *a) {
	data *dt = (data*)a;
	pthread_barrier_wait(&barrier);
	for(int i = 0; i < n; i++) {
		sem_wait(&sems[i]);
		printf("Thread %d enters checkpoint %d\n", dt->id, i);
		usleep(1000);
		sem_post(&sems[i]);
	}

	printf("Thread %d finished\n", dt->id);

	return NULL;
}

int main(int argc, char** argv) {
	if(argc < 2) {
		perror("Please insert one argument\n");
		exit(0);
	}

	n = atoi(argv[1]);
	m = 1;
	for(int i = 1; i <= n; i++)
		m *= 2;
	
	int step = 2;
	for(int i = 0; i < n; i++) {
		sem_init(&sems[i], 0, m / step);
		step *= 2;
	}

	pthread_barrier_init(&barrier, NULL, m);
	pthread_t *t = malloc(sizeof(pthread_t) * m);
	data *d = malloc(sizeof(data) * m);
	for(int i = 0; i < m; i++) {
		d[i].id = i;
		if(pthread_create(&t[i], NULL, fa, &d[i]) < 0) {
			perror("Error on create thread\n");
			exit(0);
		}
	}

	for(int i = 0; i < m; i++)
		pthread_join(t[i], NULL);
	
	return 0;
}

