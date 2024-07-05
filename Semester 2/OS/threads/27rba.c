#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#define BUFFER_SIZE 128

typedef struct {
    int m;
    int nrs;
    char s[BUFFER_SIZE + 1]; // buffer to hold the string + null terminator
    int curr_pos; // current position in the buffer
} data;

int N, M;
pthread_mutex_t m;
pthread_cond_t c1, c2;

void *generator(void *a) {
    data* dt = (data*)a;

    while (1) {
        pthread_mutex_lock(&m);
        if (dt->nrs == 0) {
            pthread_mutex_unlock(&m);
            break;
        }

        if (dt->curr_pos < BUFFER_SIZE) {
            char ch = rand() % 26 + 'a';
            dt->s[dt->curr_pos++] = ch;

            if (dt->curr_pos == BUFFER_SIZE) {
                dt->s[BUFFER_SIZE] = '\0'; // null-terminate the string
                pthread_cond_signal(&c1);
            }
        }
        
        pthread_mutex_unlock(&m);
    }

    return NULL;
}

void *printer(void *a) {
    data* dt = (data*)a;

    while (1) {
        pthread_mutex_lock(&m);
        
        while (dt->curr_pos < BUFFER_SIZE && dt->nrs > 0) {
            pthread_cond_wait(&c1, &m);
        }

        if (dt->nrs == 0) {
            pthread_mutex_unlock(&m);
            break;
        }

        printf("%s\n", dt->s);
        dt->curr_pos = 0;
        dt->nrs--;

        pthread_cond_broadcast(&c2);
        pthread_mutex_unlock(&m);
    }

    return NULL;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        perror("Invalid number of arguments\n");
        exit(1);
    }

    N = atoi(argv[1]);
    M = atoi(argv[2]);

    pthread_t th[N + 1];
    data d;

    d.m = M;
    d.nrs = M;
    d.curr_pos = 0;

    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&c1, NULL);
    pthread_cond_init(&c2, NULL);

    srand(time(NULL));

    if (pthread_create(&th[N], NULL, printer, &d) != 0) {
        perror("Error creating printer thread\n");
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        if (pthread_create(&th[i], NULL, generator, &d) != 0) {
            perror("Error creating generator thread\n");
            exit(1);
        }
    }

    for (int i = 0; i < N; i++) {
        pthread_join(th[i], NULL);
    }

    // Ensure the printer thread completes after all generators are done
    pthread_mutex_lock(&m);
    d.nrs = 0;
    pthread_cond_signal(&c1);
    pthread_mutex_unlock(&m);

    pthread_join(th[N], NULL);

    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&c1);
pthread_cond_destroy(&c2);

    return 0;
}

