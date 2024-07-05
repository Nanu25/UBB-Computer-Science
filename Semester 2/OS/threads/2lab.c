#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

/*
 *Se dă un tablou care conține 100.000 de numere întregi. Folosind un număr potrivit de thread-uri
și cele mai potrivite mecanisme de sincronizare, să se calculeze diferența absolută dintre valoarea minimă
determinată în fiecare interval de 2000 de numere consecutive și media aritmetică a tuturor valorilor minime.
 */

#define TMAX 50

int v[100005], n, difmin = 9999999, minst, mindr;
pthread_mutex_t m;

void *f(void *a) {
	int *id = (int*)a;
	
	pthread_mutex_lock(&m);

	int st = *id * 2000;
	int dr = st + 2000;
	
	printf("%d %d\n", st, dr);
	
	for(int i = st; i < dr; i++) {

		for(int j = i + 1; j < dr; j++) {
			if(abs(v[j] - v[i]) < difmin) {
				difmin = abs(v[j] - v[i]);
				minst = v[i];
				mindr = v[j];
			}
		}
	}

	pthread_mutex_unlock(&m);
	

	return NULL;
}

int main(int argc, char **argv) {
	srandom(getpid());
	
	n = 100000;
	for(int i = 0; i < n; i++)
		v[i] = rand();


	pthread_mutex_init(&m, NULL);
	pthread_t t[TMAX];
	
	for(int i = 0; i < TMAX; i++) {
		int *x = malloc(sizeof(int));
		*x = i;
		if(pthread_create(&t[i], NULL, f, x) < 0) {
			perror("Error on create thread\n");
			exit(0);
		}
	}

	for(int i = 0; i < TMAX; i++)
		pthread_join(t[i], NULL);

	pthread_mutex_destroy(&m);
	printf("%d\n", difmin);
	printf("%d %d\n", minst, mindr);

	return 0;
}

