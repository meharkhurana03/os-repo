#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <time.h>
#include <sched.h>

#define BILLION 1000000000L;



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
    printf("Thread A\n");
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
    printf("Thread B\n");
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
    printf("Thread C\n");
    pthread_exit(NULL);
}



int main(int argc, char *argv[]) {
    
    pthread_t threadA;
    pthread_t threadB;
    pthread_t threadC;

    double time_elapsed1;
    double time_elapsed2;
    double time_elapsed3;
    // struct sched_param pA;
    // struct sched_param pB;
    // struct sched_param pC;

    struct sched_param pA;
    struct sched_param pB;
    struct sched_param pC;

    memset(&pA, 0, sizeof(struct sched_param));
    memset(&pB, 0, sizeof(struct sched_param));
    memset(&pC, 0, sizeof(struct sched_param));

    if (argc < 2){
        pA.sched_priority = 0;
        pB.sched_priority = 1;
        pC.sched_priority = 1;
    } else {
        pA.sched_priority = atoi(argv[1]);
        pB.sched_priority = atoi(argv[2]);
        pC.sched_priority = atoi(argv[3]);
    }
    
    
    // pA.sched_priority = 19;

    
    
    pthread_create(&threadA, NULL, thrA, (void *)&time_elapsed1);
    pthread_create(&threadB, NULL, thrB, (void *)&time_elapsed2);
    pthread_create(&threadC, NULL, thrC, (void *)&time_elapsed3);
    // pthread_create(&threadB, NULL, thrB, "B");
    // pthread_create(&threadC, NULL, thrC, "C");

    pthread_setschedparam(threadA, SCHED_OTHER, &pA);
    pthread_setschedparam(threadB, SCHED_RR, &pB);
    pthread_setschedparam(threadC, SCHED_FIFO, &pC);


    // pB.sched_priority = 99;

    // pC.sched_priority = 1;

    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);


    printf("Thread A: %lf\n", time_elapsed1);
    printf("Thread B: %lf\n", time_elapsed2);
    printf("Thread C: %lf\n", time_elapsed3);
    fprintf(stdout, "%u\n", pA.sched_priority);
    fprintf(stdout, "%u\n", pB.sched_priority);
    fprintf(stdout, "%u\n", pC.sched_priority);
    
    FILE *fout = fopen("outputpart1.txt", "w");

    if (fout == NULL){
        printf("Error opening files.\n");
        exit(1);
    }

    fprintf(fout, "%lf\n", time_elapsed1);
    fprintf(fout, "%lf\n", time_elapsed2);
    fprintf(fout, "%lf\n", time_elapsed3);
    fprintf(fout, "%u\n", pA.sched_priority);
    fprintf(fout, "%u\n", pB.sched_priority);
    fprintf(fout, "%u\n", pC.sched_priority);

    


    
    
    // printf("%d\n", sched_get_priority_max(SCHED_FIFO));
    // printf("%d\n", sched_get_priority_min(SCHED_FIFO));
    // printf("%d\n", sched_get_priority_max(SCHED_OTHER));
    // printf("%d\n", sched_get_priority_min(SCHED_OTHER));
    // printf("%d\n", sched_get_priority_max(SCHED_RR));
    // printf("%d\n", sched_get_priority_min(SCHED_RR));
    
}
