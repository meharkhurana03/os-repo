#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>


#define BUFFERSIZE 10
#define FIFONAME1 "myFIFO1"
#define FIFONAME2 "myFIFO2"
#define BIL 1000000000;

int main() {
    char buf[BUFFERSIZE];

    struct timespec t_begin, t_end;
    int n;
    int fd_write;
    int fd_read;

    char str[50][10];
    for (int i = 0; i < 50; i++) {
        str[i][0] = i + 1;
    }
    for (int i = 0; i < 50; i++) {
		for (int j = 1; j < 9; j++) {
			str[i][j] = rand()%92 + 33;
		}
        str[i][9] = '\0';
	}

    // printf("\n********************************\n");
    // printf("%d\n", str[0][0]);
    // printf("%d\n", str[0][1]);
    // printf("%d\n", str[0][2]);
    // printf("%d\n", str[0][3]);
    // printf("%d\n", str[0][4]);
    // printf("%d\n", str[0][5]);
    // printf("%d\n", str[0][6]);
    // printf("%d\n", str[0][7]);
    // printf("%d\n", str[0][8]);
    // printf("%d\n", str[0][9]);


    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 9; j++) {
            if (j == 0) {
                printf("%d : ", str[i][j]); 
            } else {
                printf("%c", str[i][j]);
            }
        }
        printf("\n");
    }

    // printf("\n********************************");
    mkfifo(FIFONAME1, 0666);
    mkfifo(FIFONAME2, 0666);
    
    clock_gettime(CLOCK_REALTIME, &t_begin);

    int response;
    int min_id = 0;
    while(1) {
        for(int i = 0; i < 5; i++) {
            fd_write = open(FIFONAME1, O_WRONLY);
            write(fd_write, str[min_id], 10);
            close(fd_write);
        }

        // for(int i = min_id; i<min_id + 5; i++){
        //     fd_write = open(FIFONAME1, O_WRONLY);

        //     response = write(fd_write, str[i], 10);
        //     if (response == -1) {
        //         perror("Problem in writing to writing FIFO in P1.");
        //         exit(1);
        //     }

        //     close(fd_write);
        // }


        fd_read = open(FIFONAME2, O_RDONLY);
        int response2 = read(fd_read, buf, BUFFERSIZE);
        close(fd_read);
        if (response2 == -1) {
            perror("Problem in reading from reading FIFO in P1.");
            exit(1);
        }

        int max_id_received = buf[0];
        printf("Max ID received by P2 : %d\n", max_id_received);
        
        min_id = 1 + max_id_received;
        if (min_id >= 50) {
            clock_gettime(CLOCK_REALTIME, &t_end);
            double time = (double) (t_end.tv_sec - t_begin.tv_sec) + (t_end.tv_nsec - t_begin.tv_nsec) / (double) BIL;
            printf("Time taken : %f\n", time);
            exit(0);
        }
    }

}