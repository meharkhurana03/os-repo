#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <time.h>
#include <sched.h>


void* thrA(void *arg){
    for (int i=0; i<200000; i++){
        printf("%d %s\n", i, (char *) arg);
    }
    return NULL;
}

int main() {
    pthread_t p1, p2;
    int rc;
    printf("main: begin\n");
    pthread_create(&p1, NULL, thrA, "A");
    pthread_create(&p2, NULL, thrA, "B");
    // join waits for the threads to finish
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    printf("main: end\n");
}