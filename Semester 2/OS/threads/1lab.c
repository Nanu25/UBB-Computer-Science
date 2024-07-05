#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct {
	int v[105];
	int n;
}data;

void *f(void *a) {
	data* dt = (data*)a;

	int minim = dt->v[0];
	for(int i = 1; i < dt->n; i++) {
		minim = (minim < dt->v[i] ? minim : dt->v[i]); 
	}

	printf("The minimum value is %d\n", minim);

	return NULL;	
}

int main(int argc, char** argv) {

	data* d = malloc(sizeof(data));
	printf("Please insert n\n");
	int n;
	scanf("%d", &n);
	d->n = n;
	for(int i = 0; i < d->n; i++) {
		scanf("%d", &d->v[i]);
	}

	pthread_t t;

	if(pthread_create(&t, NULL, f, d) < 0) {
		perror("Error on creating pthread\n");
		exit(0);
	}

	pthread_join(t, NULL);

	return 0;
}
