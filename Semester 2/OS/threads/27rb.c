/*
 *Write a C program that takes two numbers, N and M, as arguments from the command line. The program creates N "generator" threads that generate random lowercase letters and append them to a string with 128 positions. The program will create an additional "printer" thread that that waits until all the positions of the string are filled, at which point it prints the string and clears it. The N "generator" threads must generate a total of M such strings and the "printer" thread prints each one as soon as it gets to length 128.
 * */
 

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

typedef struct {
	int m;
	int nrs;
	char s[130];
}data;

int N, M;
pthread_mutex_t m;
pthread_cond_t c1, c2;

void *generator(void *a) {
	data* dt = (data*)a;

	int size = 127;
	while(size>=0) {
		pthread_mutex_lock(&m);
		char ch = rand() % 26 + 'a';
		dt->s[size--] = ch;
		if(size == -1) {
			pthread_cond_signal(&c1);
		while(size == -1)
		       	pthread_cond_wait(&c2, &m);	
		}
		pthread_mutex_unlock(&m);
		
	}

	return NULL;
}

void *printer(void *a) {
        data* dt = (data*)a;
        
	
	while(dt->nrs != 0) {
		pthread_mutex_lock(&m);
		printf("%s\n", dt->s);
		if(dt->nrs != 0) {
			pthread_cond_signal(&c2);
			while(dt->nrs != 0) 
				pthread_cond_wait(&c1, &m);

		}
		dt->nrs--;
		pthread_mutex_unlock(&m);
	}
	
	return NULL;
}

int main(int argc, char **argv) {
	if(argc != 3) {
		perror("Invalid number of arguments\n");
		exit(0);
	}	


	N = atoi(argv[1]);
	M = atoi(argv[2]);
	pthread_t th[N + 1];
	data *d = malloc(sizeof(data) * (N + 1));

	pthread_mutex_init(&m, NULL);

       d[N].nrs = N;
        if(pthread_create(&th[N], NULL, printer, &d[N]) < 0) {
                perror("Error on create thread\n");
                exit(0);
        }

	for(int i = 0; i < N; i++) {
		d[i].m = M;
		if(pthread_create(&th[i], NULL, generator, &d[i]) < 0) {
			perror("Error on create thread\n");
			exit(0);
		}
	}

	for(int i = 0; i < N; i++) {
		pthread_join(th[i], NULL);
	}


	//pthread_join(th[N], NULL);

	pthread_mutex_destroy(&m);

	return 0;

}


