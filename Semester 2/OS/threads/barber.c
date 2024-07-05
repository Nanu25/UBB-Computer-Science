#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int freechairs=3;
pthread_mutex_t m;
sem_t barbersem, clientsem;


void *fclient(void *a) {
	int *id = (int*)a;
	
	if(freechairs > 0) {
		printf("Client %d started\n", *id);
		
		sem_post(&clientsem);
		pthread_mutex_lock(&m);	//lock resources.
		
		freechairs--;

		pthread_mutex_unlock(&m);
		sem_wait(&barbersem);
		printf("Client %d finished\n", *id);
	}else {
		printf("Client %d left\n", *id);
	}

	return NULL;
}

void *fbarber(void *a) {
	printf("Barber is waiting\n");
	while(1) {
		printf("Barber is sleeping\n");
		sem_wait(&clientsem);
		pthread_mutex_lock(&m);
		freechairs++;
		pthread_mutex_unlock(&m);
		sem_post(&barbersem);
	}
	return NULL;
}

int main(int argc, char** argv) {
	if(argc < 2) {
		perror("Please insert the number of clients\n");
		return 0;
	}

	int n = atoi(argv[1]);
	pthread_t *t = malloc(sizeof(pthread_t) * n);
	pthread_t tb;
	pthread_mutex_init(&m, NULL);
	if(pthread_create(&tb, NULL, fbarber, NULL) < 0) {
		perror("Error on creating barber thread\n");
		exit(0);
	}

	for(int i = 0; i < n; i++) {
		int *p = malloc(sizeof(int));
		*p = i;
		if(pthread_create(&t[i], NULL, fclient, p) < 0) {
			perror("Unable to create clients\n");
			exit(0);
		}
	}

	pthread_join(tb, NULL);
	for(int i = 0; i < n; i++) 
		pthread_join(t[i], NULL);

	pthread_mutex_destroy(&m);
	free(t);

	return 0;
}
