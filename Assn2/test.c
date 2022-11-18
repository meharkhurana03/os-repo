#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <time.h>
#include <sched.h>
#include <stdbool.h>


void* thrA(void *arg){
    for (int i=0; i<200000; i++){
        printf("%d %s\n", i, (char *) arg);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    bool x = (sizeof(atoi(argv[1])) == sizeof(int));
    printf("%d\n", x);
}