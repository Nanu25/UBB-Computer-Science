#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct {
	int letters, digits, special;
	char *str;
	
	
}data;

pthread_mutex_t m1, m2, m3;

void *compute(void *a) {
	data *dt = (data*) a;

	for(int i = 0; i < strlen(dt->str); i++) {
		if(dt->str[i] >= 'a' && dt->str[i] <= 'z') {
			pthread_mutex_lock(&m1);
			dt->letters += 1;
			pthread_mutex_unlock(&m1);
		}else if(dt->str[i] >= '0' && dt->str[i] <= '9') {
		 	pthread_mutex_lock(&m2);
			dt->digits += 1;
			 pthread_mutex_unlock(&m2);
		}
		else {
		 	pthread_mutex_lock(&m3);
			dt->special++;
			pthread_mutex_unlock(&m3);
		}
	
	}		

	return NULL;
}

int main(int argc, char** argv) {
	if(argc < 2) {
		printf("Please insert one argument\n");
		return 0;
	}


	pthread_t *t = malloc(sizeof(pthread_t) * (argc - 1));
	data *d = malloc(sizeof(data) * (argc - 1));


	pthread_mutex_init(&m1, NULL);
        pthread_mutex_init(&m2, NULL);
        pthread_mutex_init(&m3, NULL);

	for(int i = 0; i < argc - 1; i++) {
		d[i].letters = 0;
        	d[i].digits = 0;
        	d[i].special = 0;
		d[i].str = argv[i + 1];
		if(pthread_create(&t[i], NULL, compute, &d[i]) < 0) {
			perror("Error on create a thread\n");
			exit(0);
		}
	}	


	for(int i = 0; i < argc - 1; i++) {
		if(pthread_join(t[i], NULL) < 0) {
                        perror("Error on create a thread\n");
                        exit(0);
		}
	}


	int l = 0, di = 0, s = 0;
	for(int i = 0; i < argc - 1; i++) {
		l += d[i].letters;
		di += d[i].digits;
		s += d[i].special;
	}

	printf("Total letters: %d, total digits: %d, total specials: %d \n", l, di, s);
	
        pthread_mutex_destroy(&m1);
        pthread_mutex_destroy(&m2);
        pthread_mutex_destroy(&m3);

	free(t);
	free(d);

	return 0;
}
