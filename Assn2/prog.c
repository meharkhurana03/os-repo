#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <time.h>
#include <sched.h>

#define BILLION 1000000000L;

double time_elapsed1;
double time_elapsed2;
double time_elapsed3;

void countA() {
    unsigned int counter = 0;
    while (counter < UINT_MAX) {
        // if (counter % 10000 == 0){
        //     printf("%u", counter);
        // }
        counter++;
    }
}

void countB() {
    unsigned int counter = 0;
    while (counter < UINT_MAX){
        // if (counter % 10000 == 0){
        //     printf("%u", counter);
        // }
        counter++;
    }
}

void countC() {
    unsigned int counter = 0;
    while (counter < UINT_MAX){
        // if (counter % 10000 == 0){
        //     printf("%u", counter);
        // }
        counter++;
    }
}

void* thrA(void *arg){
    printf("Thread A\n");
    double *time_elapsed1 = (double *)arg;

    struct timespec start, finish;
    clock_gettime(CLOCK_REALTIME, &start);
    countA();
    clock_gettime(CLOCK_REALTIME, &finish);

    *time_elapsed1 = (finish.tv_sec - start.tv_sec) + (double) (finish.tv_nsec - start.tv_nsec) / BILLION;
    pthread_exit(NULL);
}

void* thrB(void *arg){
    printf("Thread B\n");
    double *time_elapsed2 = (double *)arg;

    struct timespec start, finish;
    clock_gettime(CLOCK_REALTIME, &start);
    countB();
    clock_gettime(CLOCK_REALTIME, &finish);

    *time_elapsed2 = (finish.tv_sec - start.tv_sec) + (double) (finish.tv_nsec - start.tv_nsec) / BILLION;
    pthread_exit(NULL);
}

void* thrC(void *arg){
    printf("Thread C\n");
    double *time_elapsed3 = (double *)arg;

    struct timespec start, finish;
    clock_gettime(CLOCK_REALTIME, &start);
    countC();
    clock_gettime(CLOCK_REALTIME, &finish);

    *time_elapsed3 = (finish.tv_sec - start.tv_sec) + (double) (finish.tv_nsec - start.tv_nsec) / BILLION;
    pthread_exit(NULL);
}



int main(int argc, char *argv[]) {
    
    pthread_t threadA;
    pthread_t threadB;
    pthread_t threadC;

    // struct sched_param pA;
    // struct sched_param pB;
    // struct sched_param pC;

    

    if (argc < 2){
        // pA.sched_priority = 1;
        // pB.sched_priority = 0;
        // pC.sched_priority = 0;
    } else {
        // pA.sched_priority = atoi(argv[1]);
        // pB.sched_priority = atoi(argv[2]);
        // pC.sched_priority = atoi(argv[3]);
    }
    struct sched_param pA;
    memset(&pA, 0, sizeof(struct sched_param));
    pA.sched_priority = 0;

    pthread_setschedparam(threadA, SCHED_OTHER, &pA);

    pthread_create(&threadA, NULL, thrA, (void *)&time_elapsed1);
    // pthread_create(&threadB, NULL, thrB, "B");
    // pthread_create(&threadC, NULL, thrC, "C");

    struct sched_param pB;
    memset(&pB, 0, sizeof(struct sched_param));
    pB.sched_priority = 1;

    pthread_setschedparam(threadB, SCHED_RR, &pB);

    pthread_create(&threadB, NULL, thrB, (void *)&time_elapsed2);

    struct sched_param pC;
    memset(&pC, 0, sizeof(struct sched_param));
    pC.sched_priority = 10;

    pthread_setschedparam(threadC, SCHED_FIFO, &pC);

    pthread_create(&threadC, NULL, thrC, (void *)&time_elapsed3);

    
    

    pthread_join(threadA, NULL);
    pthread_join(threadC, NULL);
    pthread_join(threadB, NULL);


    printf("Thread A: %lf\n", time_elapsed1);
    printf("Thread B: %lf\n", time_elapsed2);
    printf("Thread C: %lf\n", time_elapsed3);
    


    
    
    // printf("%d\n", sched_get_priority_max(SCHED_FIFO));
    // printf("%d\n", sched_get_priority_min(SCHED_FIFO));
    // printf("%d\n", sched_get_priority_max(SCHED_OTHER));
    // printf("%d\n", sched_get_priority_min(SCHED_OTHER));
    // printf("%d\n", sched_get_priority_max(SCHED_RR));
    // printf("%d\n", sched_get_priority_min(SCHED_RR));
    
}
