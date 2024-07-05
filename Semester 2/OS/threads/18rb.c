#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct {
	char *s;
}data;

pthread_mutex_t m;

void *fa(void *a) {
	data* dt = (data*) a;
	
	pthread_mutex_lock(&m);
	for(int i = 0; i < strlen(dt->s); i++) {
		if(dt->s[i] >= 'a' && dt->s[i] <= 'z') {
			dt->s[i] -= 32;
		}
	}
	pthread_mutex_unlock(&m);


	return NULL;
}

int main(int argc, char** argv) {
	if(argc < 2) {
		perror("Please insert at least one argument\n");
		exit(0);
	}

	pthread_mutex_init(&m, NULL);	
	data *d = malloc(sizeof(data) * (argc - 1));
	pthread_t *t = malloc(sizeof(pthread_t) * (argc - 1));
	for(int i = 0; i < argc - 1; i++) {
		d[i].s = argv[i + 1];
		if(pthread_create(&t[i], NULL, fa, &d[i]) < 0) {
			perror("Error on create thread\n");
			exit(0);
		}
	}


	for(int i = 0; i < argc - 1; i++) {
		pthread_join(t[i], NULL);
	}

	for(int i = 0; i < argc - 1; i++) {
		printf("%s\n", d[i].s);
	}
	
	pthread_mutex_destroy(&m);

	return 0;
}

