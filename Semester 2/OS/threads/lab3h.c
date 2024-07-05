#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
typedef struct {
	int id;
}data;

int index;
int x;
int find = 0;
pthread_mutex_t m;
pthread_barrier_t b, b2;
pthread_cond_t c1;


void *fa(void *a) {
	data *d = (data*) a;

	printf("Thread %d started\n", d->id);

	pthread_barrier_wait(&b);

	while(1) {
		pthread_mutex_lock(&m);

		int y = rand() % 1000;
		if(y == x) {
			find = 1;
			index = d->id;
			printf("Thread %d found %d\n", d->id, y);
			pthread_cond_signal(&c1);
			pthread_mutex_unlock(&m);
			break;
		}

		pthread_mutex_unlock(&m);

		if(find == 1)
			break;

	}
	

	printf("Thread %d finished\n", d->id);

	return NULL;
}


void *fb(void *a) {
	data* d = (data*) a;
	

	while(find == 0)
		pthread_cond_wait(&c1, &m);	

	
 	printf("Thread %d found %d\n", index, x);

	return NULL;
}

int main(int argc, char **argv) {
	if(argc < 2) {
		perror("Invalid number of arguments\n");
		exit(1);
	}
	
	srandom(getpid());
	int n = atoi(argv[1]);
	x = rand() % 1000;

	printf("x=%d\n", x);

	pthread_mutex_init(&m, NULL);
	pthread_barrier_init(&b, NULL, n);

	pthread_t *th = malloc(sizeof(pthread_t) * (n + 1));
	data *d = malloc(sizeof(data) * n);
	for(int i = 0; i < n; i++) {
		d[i].id = i;
		if(pthread_create(&th[i], NULL, fa, &d[i]) < 0) {
			perror("Unable to create pthread\n");
			exit(0);
		}
	}

	for(int i = 0; i < n; i++) {
		pthread_join(th[i], NULL);
	}


	pthread_create(&th[n], NULL, fb, NULL);
	pthread_join(th[n], NULL);


	free(th);
	free(d);
	pthread_mutex_destroy(&m);
	pthread_barrier_destroy(&b);
	return 0;
}

