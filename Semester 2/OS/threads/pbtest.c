#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
	int id;
}data;

int s;
pthread_mutex_t m;
pthread_barrier_t b;

void *fa(void *a) {
	data* d = (data*) a;

	printf("Thread %d started\n", d->id);
	
	int v[3];
	for(int i = 0; i < 3; i++) {
		v[i] = rand() % 10 + 1;
		printf("Thread %d generated %d\n", d->id, v[i]);
	}

        pthread_barrier_wait(&b);

        pthread_mutex_lock(&m);
	for(int i = 0; i < 3; i++)  {
		if(v[i] % 2 == 0)
			s -= v[i];
		else s += v[i];
	
	}
	pthread_mutex_unlock(&m);

	return NULL;
}


int main(int argc, char** argv) {
	if(argc != 2) {
		perror("Invalid number of arguments\n");
		exit(1);
	}
	
	srandom(getpid());
	int n = atoi(argv[1]);
	pthread_mutex_init(&m, NULL);
	pthread_barrier_init(&b, NULL, n);

	pthread_t *th = malloc(sizeof(pthread_t) * n);
	data* dt = malloc(sizeof(data) * n);
	for(int i = 0; i < n; i++) {
		dt[i].id = i;
		if(pthread_create(&th[i], NULL, fa, &dt[i]) < 0) {
			perror("Error on creating thread\n");
			exit(1);
		}
	}	


	for(int i = 0; i < n; i++)
		pthread_join(th[i], NULL);


	free(dt);
	free(th);
	pthread_mutex_destroy(&m);
	pthread_barrier_destroy(&b);
	
	printf("The sum is %d \n", s);

	return 0;
}


