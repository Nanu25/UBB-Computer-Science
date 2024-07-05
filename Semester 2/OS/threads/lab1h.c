#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

typedef struct {
	int id;
}data;
int n;
int s;
pthread_mutex_t m;
pthread_barrier_t b;

void *fa(void *a) {
	data* d = (data*) a;
	printf("Thread %d started\n", d->id);

	while(s >= -500 && s <= 500) {
		pthread_mutex_lock(&m);
		int x = rand() % 100;
		s += x - 50;
		
		if(abs(s) > 500) {
			pthread_mutex_unlock(&m);
			break;
		}

		printf("Thread %d have the sum %d\n", d->id, s);
		pthread_mutex_unlock(&m);

	}

	pthread_barrier_wait(&b);
	printf("Thread %d finished\n", d->id);

	return NULL;
}

int main(int argc, char** argv) {
	if(argc != 2) {
		perror("Please insert one argument\n");
		exit(0);
	}

	srandom(getpid());
	n = atoi(argv[1]);
	
	pthread_mutex_init(&m, NULL);
	pthread_barrier_init(&b, NULL, n);
	pthread_t *th = malloc(sizeof(pthread_t) * n);
	data *dt = malloc(sizeof(data) * n);
	for(int i = 0; i < n; i++) {
		dt[i].id = i;
		if(pthread_create(&th[i], NULL, fa, &dt[i])  < 0) {
			perror("Error on creating thread\n");
			exit(0);
		}
	}


	for(int i = 0; i < n; i++)
		pthread_join(th[i], NULL);

	printf("The sum is %d\n", s);

	free(th);
	free(dt);
	pthread_mutex_destroy(&m);
	pthread_barrier_destroy(&b);

	return 0;
}
