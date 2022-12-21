#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int resource[5];
int bowl1;
int bowl2;

void thinking(int id) {
    printf("Philosopher %d is thinking.\n", id);
}

void eating(int id) {
    printf("Philosopher %d is eating.\n", id);
    sleep(1);
}

void stopped_eating(int id) {
    printf("Philosopher %d has stopped eating.\n", id);
}

void *phil(void *arg) {
    int id = *(int*)arg;


    while (1) {
        int bowl = 0;
        if (id == 4) {
            thinking(id);
            while (resource[(id + 1) % 5]);
            
            resource[(id + 1) % 5] = 1;
            printf("Philosopher %d took %d\n", id, (id + 1) % 5);
            while (resource[id]);
            
            resource[id] = 1;
            printf("Philosopher %d took %d\n", id, id);
            while (bowl1 && bowl2);
            if (bowl1 == 1) {
                
                bowl2 = 1;
                bowl = 2;
                printf("Philosopher %d took     bowl %d\n", id, 2);
            } else {
                
                bowl1 = 1;
                bowl = 1;
                printf("Philosopher %d took     bowl %d\n", id, 1);
            }

            eating(id);

            printf("Philosopher %d released %d\n", id, (id + 1) % 5);
            resource[(id + 1) % 5] = 0;
            printf("Philosopher %d released %d\n", id, id);
            resource[id] = 0;

            if (bowl == 1) {
                printf("Philosopher %d released bowl %d\n", id, 1);
                bowl1 = 0;
            } else {
                printf("Philosopher %d released bowl %d\n", id, 2);
                bowl2 = 0;
            }

            stopped_eating(id);
        } else {
            thinking(id);

            while (resource[(id)]);
            resource[id] = 1;
            printf("Philosopher %d took %d\n", id, id);
            while (resource[(id + 1)%5]);
            resource[(id + 1) % 5] = 1;
            printf("Philosopher %d took %d\n", id, (id + 1) % 5);
            while (bowl1 && bowl2);
            if (bowl1 == 1) {
                bowl2 = 1;
                bowl = 2;
                printf("Philosopher %d took     bowl %d\n", id, 2);
            } else {
                bowl1 = 1;
                bowl = 1;
                printf("Philosopher %d took     bowl %d\n", id, 1);
            }

            eating(id);

            printf("Philosopher %d released %d\n", id, id);
            resource[id] = 0;
            printf("Philosopher %d released %d\n", id, (id + 1) % 5);
            resource[(id + 1) % 5] = 0;

            if (bowl == 1) {
                printf("Philosopher %d released bowl %d\n", id, 1);
                bowl1 = 0;
            } else {
                printf("Philosopher %d released bowl %d\n", id, 2);
                bowl2 = 0;
            }

            stopped_eating(id);
        }
    }
}

int main() {
    for (int i = 0; i < 5; i++){
        resource[i] = 0;
    }
    bowl1 = 0;
    bowl2 = 0;

    pthread_t id1;
    pthread_t id2;
    pthread_t id3;
    pthread_t id4;
    pthread_t id5;

    int a = 0, b = 1, c = 2, d = 3, e = 4;

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
