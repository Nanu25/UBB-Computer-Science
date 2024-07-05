#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

int v[1005], n;
pthread_mutex_t m;
pthread_cond_t c;

void *fa(void *a) {
	int *id = (int*)a;
	printf("Thread %d started\n", *id);
	
	pthread_mutex_lock(&m);
	v[*id] = rand() % 10 + 10;
	
	//int full = 1;
	//for(int i = 0; i < n; i++) {
	//	if(v[i] != 0) 
	//		full = 0;
	//}
	
	

	
	//while(full == 0)
	//	pthread_cond_wait(&c, &m);
	
	//pthread_cond_signal(&c);
	pthread_mutex_unlock(&m);


	return NULL;
}

int main(int argc, char **argv) {
	
	srandom(getpid());
	scanf("%d", &n);
	
	pthread_mutex_init(&m, NULL);
	pthread_t *th = malloc(sizeof(pthread_t) * n);
	
	for(int i = 0; i < n; i++) {
		int *p = malloc(sizeof(int));
		*p = i;
		if(pthread_create(&th[i], NULL, fa, p) < 0) {
			perror("Error on creating thread\n");
			exit(0);
		}
	}

	for(int i = 0; i < n; i++)
		pthread_join(th[i], NULL);

	pthread_mutex_destroy(&m);

	return 0;

}
