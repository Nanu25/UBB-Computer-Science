/*
 * Write a C program that reads a matrix of integers from a file. It then creates as many threads as there are rows in the matrix, each thread calculates the sum of the numbers on a row. The main process waits for the threads to finish, then prints the sums.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
typedef struct {
	int id;
	int s;
}data;

int n, m;
int a[105][105];
pthread_mutex_t mt;
pthread_barrier_t b;

void *fa(void *c) {
	data* d = (data*) c;
	
	printf("Thread %d started\n", d->id);
	
	pthread_barrier_wait(&b);
	
	pthread_mutex_lock(&mt);


	int sum = 0;
	int i = d->id;
	for(int j = 0; j < m; j++)
		sum += a[i][j];
	
	d->s = sum;
	pthread_mutex_unlock(&mt);

	printf("Thread %d finished\n", d->id);
	
	return NULL;
}

int main(int argc, char** argv) {
	
	FILE *file = fopen("matrix.txt", "r");
	
	fscanf(file, "%d", &n);
	fscanf(file, "%d", &m);
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			fscanf(file, "%d", &a[i][j]);
		}
	}

	pthread_barrier_init(&b, NULL, n);
	pthread_mutex_init(&mt, NULL);
	pthread_t *th = malloc(sizeof(pthread_t) * n);
	data* d = malloc(sizeof(data) * n);
	for(int i = 0; i < n; i++) {
		d[i].id = i;
		if(pthread_create(&th[i], NULL, fa, &d[i]) < 0) {
			perror("Error on creating thread\n");
			exit(0);
		}
	}

	for(int i = 0; i < n; i++)
		pthread_join(th[i], NULL);

	for(int i = 0; i < n; i++)
		printf("%d\n", d[i].s);

	free(d);
	free(th);
	pthread_mutex_destroy(&mt);
	pthread_barrier_destroy(&b);

	return 0;
}

