#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <sched.h>
#include <sys/wait.h>
#include <unistd.h>

#define BIL 1000000000L;

void run_proc(pid_t pid, int proc, int priority, FILE* outf);

int main(int argc, char *argv[]){

    pid_t pid1, pid2, pid3;
    FILE *outf = fopen("result12.txt", "w");
    
    int priority1, priority2, priority3;
    if (argc == 1) {
        priority1 = atoi(argv[1]);
        priority2 = atoi(argv[2]);
        priority3 = atoi(argv[3]);
    } else {
        priority1 = 0;
        priority2 = 1;
        priority3 = 1;
    }

    pid1 = fork();
    printf("first fork.\n");
    if (pid1 == 0) {
        // PROCESS 1 - SCHED_OTHER
        printf("inside first fork.");
        run_proc(pid1, 1, priority1, outf);

    } else if (pid1 < 0){
        printf("Error in forking 1.");

    } else {
        pid2 = fork();
        if (pid2 == 0) {
            printf("inside second fork.");
        } else if (pid2 < 0) {
            printf("Error in forking 2.");
        } else {
            pid3 = fork();
            if (pid3 == 0) {
                printf("inside third fork.");
            } else if (pid3 < 0) {
                printf("Error in forking 3.");
            }
            wait(NULL);
        }
        wait(NULL);
    }


    fclose(outf);
}


void run_proc(pid_t pid, int proc, int priority, FILE *outf){
    struct timespec start, finish;
    struct sched_param parameter;
    double time_elapsed = 0.0;

    if (proc == 1) {
        pid_t pid = fork();

        parameter.sched_priority = priority;
        sched_setscheduler(getpid(), SCHED_OTHER, &parameter);

        clock_gettime(CLOCK_REALTIME, &start);
        if (pid == 0) {
            execl("/bin/sh", "sh", "/root/os-repo/Assn2/script1.sh", NULL);

        }
        else if (pid < 0) {
            printf("Error in forking.\n");
        } 
        else {
            wait(NULL);

            clock_gettime(CLOCK_REALTIME, &finish);
            time_elapsed = (finish.tv_sec - start.tv_sec) + (double) (finish.tv_nsec - start.tv_nsec) / BIL;

            printf("Time for SCHED_OTHER: %lf\n", time_elapsed);
            fprintf(outf,"A %lf\n", time_elapsed);
        }
    }

    else if (proc == 2) {
        pid_t pid = fork();

        parameter.sched_priority = priority;
        sched_setscheduler(getpid(), SCHED_RR, &parameter);

        clock_gettime(CLOCK_REALTIME, &start);
        if (pid == 0) {
            execl("/bin/sh", "sh", "/root/os-repo/Assn2/script2.sh", NULL);

        }
        else if (pid < 0) {
            printf("Error in forking.\n");
        } 

        else {
            wait(NULL);

            clock_gettime(CLOCK_REALTIME, &finish);
            time_elapsed = (finish.tv_sec - start.tv_sec) + (double) (finish.tv_nsec - start.tv_nsec) / BIL;

            printf("Time for SCHED_RR: %lf\n", time_elapsed);
            fprintf(outf,"B %lf\n", time_elapsed);
        }
    }


    else if (proc == 3) {
        pid_t pid = fork();

        parameter.sched_priority = priority;
        sched_setscheduler(getpid(), SCHED_FIFO, &parameter);

        clock_gettime(CLOCK_REALTIME, &start);
        if (pid == 0) {
            execl("/bin/sh", "sh", "/root/os-repo/Assn2/script3.sh", NULL);

        }
        else if (pid < 0) {
            printf("Error in forking.\n");
        } 

        else {
            wait(NULL);

            clock_gettime(CLOCK_REALTIME, &finish);
            time_elapsed = (finish.tv_sec - start.tv_sec) + (double) (finish.tv_nsec - start.tv_nsec) / BIL;

            printf("Time for SCHED_RR: %lf\n", time_elapsed);
            fprintf(outf,"B %lf\n", time_elapsed);
        }
    }
}