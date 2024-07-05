#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>

typedef struct {
	int n;
	int index;
	int v[100];
}data;

pthread_mutex_t m1, m2;
sem_t s;

void *feven(void *a) {
	data *d = (data*)a;
	
	while(d -> index < d -> n) {
		int x = rand() % 100;
		if(x % 2 == 1)
			x++;
		
		pthread_mutex_lock(&m1);
		printf("A\n");
		//sem_post(&s);
		d->v[d->index] = x;
		d->index++;
		pthread_mutex_unlock(&m2);
		//sem_wait(&s);
	}

	return NULL;
}

void *fodd(void *b) {
	data *d = (data*)b;
        while(d -> index < d -> n) {
                int x = rand() % 100;
                if(x % 2 == 0)
                        x++;
		
		//sem_wait(&s);
                pthread_mutex_lock(&m2);
                printf("B\n");
		d->v[d->index] = x;
                d->index++;
                pthread_mutex_unlock(&m1);
		//sem_post(&s);
        }
	return NULL;
}

int main(int argc, char ** argv) {
	if(argc < 2) {
		perror("Please insert one argument\n");
		exit(0);
	}

	srand(getpid());

	data d;
	d.n = atoi(argv[1]);	
	d.index = 0;
	printf("%d\n", d.n); 
	
	pthread_mutex_init(&m1, NULL);
	pthread_mutex_init(&m2, NULL);
	

	pthread_t t1, t2;
	
	pthread_mutex_lock(&m2);	
	if(pthread_create(&t1, NULL, feven, &d) < 0) {
	      	perror("Error on create thread\n");
      		exit(0);
	}		

	if(pthread_create(&t2, NULL, fodd, &d) < 0) {
                perror("Error on create thread\n");
                exit(0);
	}
	

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_mutex_destroy(&m1);
	pthread_mutex_destroy(&m2);

        for(int i = 0; i < d.n; i++)
                printf("%d\n", d.v[i]);


	return 0;
}

