#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
	int id;
	char s[100];
}data;


int fr[200];
pthread_mutex_t m;
pthread_barrier_t b;

void *fa(void *a) {
	data *d = (data*) a;

	printf("Thread %d started\n", d->id);
	
	
	pthread_barrier_wait(&b);


	pthread_mutex_lock(&m);

	for(int i = 0; i < strlen(d->s); i++)
		fr[d->s[i]]++;

	pthread_mutex_unlock(&m);

	printf("Thread %d finished\n", d->id);

	return NULL;
}

int main(int argc, char** argv) {
	if(argc < 2) {
		perror("Invalid number of arguments\n");
		exit(0);
	}

	
	int n = argc - 1;
	pthread_barrier_init(&b, NULL, n);
	pthread_mutex_init(&m, NULL);
	pthread_t *th = malloc(sizeof(pthread_t) * (argc + 1));
	data* dt = malloc(sizeof(data) * (argc + 1));
	
	for(int i = 0; i < argc - 1; i++) {
		dt[i].id = i;
		strcpy(dt[i].s, argv[i + 1]);
		if(pthread_create(&th[i], NULL, fa, &dt[i]) < 0) {
			perror("Unable to create thread\n");
			exit(0);
		}
	}

	for(int i = 0; i < n; i++)
		pthread_join(th[i], NULL);


	for(int i = 'a'; i <= 'z'; i++) {
		char c = i;
		if(fr[i])
			printf("Caracter %c has fr: %d \n", c, fr[i]);
	}

	pthread_mutex_destroy(&m);
	free(th);
	free(dt);
	return 0;

}

