#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
typedef struct {
	int id, w, l, lastW, n;
}data;

//0 - r
//1 - p
//2 - s

int *moves;
pthread_barrier_t *b;
pthread_barrier_t *ba;
int DoneGame = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int lostpairs = 0;

void *player(void *a) {
	data *d = (data*) a;
	int id = d->id;
	int o = id % 2==0?id + 1:id - 1;
	int bid = id / 2;
	int n = d->n;
	int localDoneGame = 0;
	int localPairs = 0;
	printf("Player %d started other player is %d \n", id, o);
	while(d->l > 0 && localDoneGame == 0 && localPairs < n) {	
		moves[id] = rand() % 3;
		printf("Player %d selected: %d \n", id, moves[id]);
		pthread_barrier_wait(&b[bid]);
		if(moves[id] == moves[o]) {
			printf("Player %d Draw\n", id);
		}else if((moves[id] == 1 && moves[o] == 2)||(moves[id] == 1 && moves[o]== 0) || (moves[id] == 2 && moves[o] == 1)) {
			printf("Player %d won\n", id);
			d->w++;
			if(d->lastW == 1) {
				d->lastW++;
			}
		}else {
			printf("Player %d lost :( \n", id);
			d->l--;
			d->lastW = 0;
		}
		pthread_mutex_lock(&m);
		if(d->w == 5)
			DoneGame = 1;
		localDoneGame = DoneGame;
		if(d->l == 0) {
			lostpairs++;
		}

		localPairs = lostpairs;
		pthread_mutex_unlock(&m);
		if(id % 2 == 0) {	
			printf("Player %d reseting the barrier \n", id);
			pthread_barrier_init(&b[bid], NULL, 2);
		}
	}	
	free(d);
	return NULL;
}

int main(int argc, char** argv) {
	if(argc != 2) {
		printf("Usage n - nr of pairs");
		exit(1);
	}

	int n = atoi(argv[1]);
	printf("Number of pairs is: %d\n", n);
	moves = (int*)malloc(2 * n * sizeof(int));
	pthread_t *th = (pthread_t*)malloc(sizeof(pthread_t) * 2 * n);

	b = (pthread_barrier_t*)malloc(sizeof(pthread_barrier_t) * n);

	for(int i = 0; i < n; i++) {
		pthread_barrier_init(&b[i], NULL, 2);
	}

        //ba = (pthread_barrier_t*)malloc(sizeof(pthread_barrier_t) * n);

        //for(int i = 0; i < n; i++) {
          //      pthread_barrier_init(&ba[i], NULL, 2);
        //}

	for(int i = 0; i < 2 * n; i++) {
		data *d = (data*)malloc(sizeof(data));
		d->id = i;
		d->w = 0;
		d->l = 3;
		d->lastW = 0;
		d->n = n;
		moves[i] = -1;
		if(pthread_create(&th[i], NULL, player, d) < 0) {
			perror("Error on creating thread\n");
			exit(2);
		}
	}

	for(int i = 0; i < 2 * n; i++) 
		pthread_join(th[i], NULL);

	free(th);
	free(moves);

	return 0;
}
