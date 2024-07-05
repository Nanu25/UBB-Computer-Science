#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
int n = 100;

void* f(void *a) {
	int i;
	for(i = 0; i < n; i++) {
		printf("%d\n", *(int *)a);
	}

	free(a);
	retur NULL;
}


int main(int argc, char** argv) {
	pthread_t t[10];
	int i, *a;

	for(i = 0; i < 10; i++) {
		a = (int *)malloc(sizeof(int));
		*a=i;
		pthread_create(&t[i], NULL, f, a);

	}

	for(i = 0; i < n; i++)
		printf("main\n");

	for(i = 0; i < 10; i++)
                pthread_join(t[i], NULL);

	return 0;

}

