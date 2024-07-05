
//Se citesc din fisier numere.Sa se afle frecventa fiecarui numar care se termina cu o cifra(de la 0 la 9)si sa se
//determine media aritmetica a frecventelor.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
	int id;
}data;

pthread_mutex_t m;
pthread_barrier_t b1;
int k, x, v[105], fr[10];
float avrage;

void *fa(void *a) {
	data *d = (data*) a;
	printf("Thread %d started for the fr\n", d->id);

	pthread_mutex_lock(&m);
	int nr = 0;

	for(int i = 0; i < k; i++)
		if(v[i] % 10 == d->id) {
			fr[v[i]]++;
			nr++;
		}

	printf("Thread %d count %d elements\n", d->id, nr);
	pthread_mutex_unlock(&m);
	
	pthread_barrier_wait(&b1);

	return NULL;
}

void *fb(void *b) {
	data *d = (data*) b;
	printf("Final thread started\n");

	pthread_mutex_lock(&m);
	
	int nr = 0;
	for(int i = 0; i < 10; i++) {
		if(fr[i]) {
			nr++;
			avrage += fr[i];
		}
	}
	avrage /= nr;
	pthread_mutex_unlock(&m);

	return NULL;
}


int main(int argc, char ** argv) {
	if(argc != 2) {
		printf("Invalid number of arguments\n");
		exit(0);
	}

	FILE* f = fopen("a.txt", "r");
	
	while(fscanf(f, "%d", &x) != EOF)  {
	       v[k++] = x;
	}	       

	pthread_barrier_init(&b1, NULL, 10);
	pthread_mutex_init(&m, NULL);
	pthread_t *th = malloc(sizeof(pthread_t) * 11);
	data *d = malloc(sizeof(data) * 11);

	for(int i = 0; i < 10; i++) {
		d[i].id = i;
		if(pthread_create(&th[i], NULL, fa, &d[i]) < 0) {
			perror("Unable to create thread\n");
			exit(0);
		}
	}

	for(int i = 0; i < 10; i++) {
		pthread_join(th[i], NULL);
	}

	if(pthread_create(&th[10], NULL, fb, NULL) < 0) {
		perror("Unable to create thread\n");
		exit(1);
	}

	pthread_join(th[10], NULL);
	printf("Avrage is %f\n", avrage); 

	free(th);
	free(d);
	pthread_mutex_destroy(&m);
	pthread_barrier_destroy(&b1);

	return 0;
}
