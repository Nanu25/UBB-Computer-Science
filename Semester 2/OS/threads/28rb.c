#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

int v[1005], n, sortat;
pthread_mutex_t m;
pthread_cond_t c;

void *fa(void *a) {
	
	while(sortat == 0) {
		pthread_mutex_lock(&m);
		int i = rand() % n;
		int j = rand() % n;

		//printf("%d %d\n", i, j);
		if(i < j) {
			if(v[i] > v[j]) {
				int aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}else {
			if(v[i] < v[j]) {
		                int aux = v[i];
                                v[i] = v[j];
                                v[j] = aux;
			}
		}
		
		sortat = 1;
		for(int k = 0; k < n - 1; k++)
			if(v[k] > v[k + 1])
				sortat = 0;
		pthread_mutex_unlock(&m);
	}

	pthread_cond_signal(&c);

	return NULL;
}

void *printer(void *a) {
	pthread_mutex_lock(&m);
	
	while(sortat == 0)
		pthread_cond_wait(&c, &m);
	
	printf("Sorted array\n");
	for(int i = 0; i < n; i++)
		printf("%d ", v[i]);
	printf("\n");

	pthread_mutex_unlock(&m);

	return NULL;
}

int main(int argc, char** argv) {
	scanf("%d", &n);

	srandom(getpid());
	for(int i = 0; i < n; i++) 
		v[i] = rand() % 1000;
	
	printf("Initial array\n");
        for(int i = 0; i < n; i++)
                printf("%d ", v[i]);
        printf("\n");


	pthread_mutex_init(&m,NULL);
	pthread_cond_init(&c, NULL);

	pthread_t *th = malloc(sizeof(pthread_t) * (n + 1));
	pthread_create(&th[n], NULL, printer, NULL); 
	for(int i = 0; i < n; i++) {
		if(pthread_create(&th[i], NULL, fa, NULL) < 0) {
			perror("Error on creating thread\n");
			exit(0);
		}

	}

	for(int i = 0; i < n; i++) 
		pthread_join(th[i], NULL);

	pthread_join(th[n], NULL);

	free(th);
	pthread_mutex_destroy(&m);
	pthread_cond_destroy(&c);

	return 0;
}

