#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

sem_t forks[5];
sem_t bowl;

void thinking(int id) {
    printf("Philosopher %d is thinking.\n", id);
}

void eating(int id) {
    printf("Philosopher %d is eating.\n", id);
}

void stopped_eating(int id) {
    printf("Philosopher %d has stopped eating.\n", id);
}

void *phil(void *arg) {
    int id = *(int*)arg;


    while (1) {
        if (id == 4) {
            thinking(id);
            sem_wait(&forks[ (id + 1) % 5 ]);
            sem_wait(&forks[ id ]);
            sem_wait(&bowl);

            eating(id);

            sem_post(&forks[ (id + 1) % 5]);
            sem_post(&forks[ id ]);
            sem_post(&bowl);

            stopped_eating(id);
        } else {
            thinking(id);

            sem_wait(&forks[ (id + 1) % 5 ]);
            sem_wait(&forks[ id ]);
            sem_wait(&bowl);

            eating(id);

            sem_post(&forks[ (id + 1) % 5]);
            sem_post(&forks[ id ]);
            sem_post(&bowl);

            stopped_eating(id);
        }
    }
}

int main() {
    for (int i = 0; i < 5; i++) {
        sem_init(&forks[i], 0, 1);
    }

    sem_init(&bowl, 0, 2);

    pthread_t id1;
    pthread_t id2;
    pthread_t id3;
    pthread_t id4;
    pthread_t id5;

    int a = 1, b = 2, c = 3, d = 4, e = 5;

    pthread_create(&id1, NULL, phil, (void *)&a);
    pthread_create(&id2, NULL, phil, (void *)&b);
    pthread_create(&id3, NULL, phil, (void *)&c);
    pthread_create(&id4, NULL, phil, (void *)&d);
    pthread_create(&id5, NULL, phil, (void *)&e);


    pthread_join(id1, NULL);
    pthread_join(id2, NULL);
    pthread_join(id3, NULL);
    pthread_join(id4, NULL);
    pthread_join(id5, NULL);
}
