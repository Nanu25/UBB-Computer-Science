#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BEARS 3
#define BEES 7

int honey = 10;
pthread_mutex_t m;
pthread_cond_t c;
sem_t s;

void* bee(void* a) {

        while(1) {
                pthread_mutex_lock(&m);
                printf("+");
                honey++;
                pthread_mutex_unlock(&m);
        }

        return NULL;
}

void* bear(void* a) {

        while(1) {
                pthread_mutex_lock(&m);
                if(honey >= 10) {
                        printf("-");
                        honey -= 10;
                } else {
                        printf("!");
                        pthread_cond_signal(&c);
                }
                pthread_mutex_unlock(&m);
        }

        return NULL;
}

void* ranger(void* a) {

        while(1) {
                pthread_mutex_lock(&m);
                while(honey >= 10) {
                        pthread_cond_wait(&c, &m);
                }
                printf("H");
                honey += 100;
                pthread_mutex_unlock(&m);
        }

        return NULL;
}

int main(int argc, char** argv) {

        pthread_t bees[BEES], bears[BEARS], ranger_t;

        pthread_mutex_init(&m, NULL);
        pthread_cond_init(&c, NULL);
        sem_init(&s, 0, 2);

        for(int i = 0; i < BEES; i++) {
                pthread_create(&bees[i], NULL, bee, NULL);
        }

        for(int i = 0; i < BEARS; i++) {
                pthread_create(&bears[i], NULL, bear, NULL);
        }

        pthread_create(&ranger_t, NULL, ranger, NULL);

        for(int i = 0; i < BEES; i++) {
                pthread_join(bees[i], NULL);
        }

        for(int i = 0; i < BEARS; i++) {
                pthread_join(bears[i], NULL);
        }

        pthread_join(ranger_t, NULL);

        pthread_mutex_destroy(&m);
        pthread_cond_destroy(&c);
        sem_destroy(&s);

        return 0;
}
