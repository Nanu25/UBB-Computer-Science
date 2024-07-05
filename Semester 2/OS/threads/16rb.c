#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct {
	int fr[15];
	char *str;
}data;

pthread_mutex_t m1;

void *compute(void *a) {
	data *d = (data*) a;
	printf("%s\n", d->str);	
	for(int i = 0; i < strlen(d->str); i++) {
		if('0' <= d->str[i] && d->str[i] <= '9') {
			pthread_mutex_lock(&m1);
			d->fr[d->str[i] - '0']++;	
			pthread_mutex_unlock(&m1);
		}
	}
	return NULL;
}

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("Please insert at least one argument\n");
		exit(0);
	}


	data *d = malloc(sizeof(data) * (argc - 1));
	pthread_mutex_init(&m1, NULL);
	pthread_t *t = malloc(sizeof(pthread_t) * (argc - 1));

	for(int i = 0; i < argc - 1; i++) {
		for(int j = 0; j <= 9; j++)
			d[i].fr[j] = 0;		//set all the fr to 0;
		
		d[i].str = argv[i + 1];
		if(pthread_create(&t[i], NULL, compute, &d[i]) < 0) {
			perror("Error on create thread\n");
			exit(0);
		}
	}

	for(int i = 0; i < argc - 1; i++)
		pthread_join(t[i], NULL);


	int ap[15];
	for(int i = 0; i <= 9; i++)
		ap[i] = 0;
	
	//Compute the total digits from all the arguments;
	for(int i = 0; i < argc - 1; i++)
	       for(int j = 0; j <= 9; j++)	
			ap[j] += d[i].fr[j];

	for(int i = 0; i <= 9; i++)
		printf("The fr of digit %d, is %d \n", i, ap[i]);

	pthread_mutex_destroy(&m1);
	free(t);
	free(d);

	return 0;
}
