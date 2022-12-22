#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>


#define BUFFERSIZE 50
#define FIFONAME1 "myFIFO1"

int main() {
    char buf[BUFFERSIZE];

    int n;
    int fd_write;
    int fd_read;

    struct timespec begin, end;

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
    printf("\n********************************\n");
    printf("%s\n", str[0]);

    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 10; j++) {
            if (j == 0) {
                printf("%d : ", str[i][j]); 
            } else {
                printf("%c", str[i][j]);
            }
        }
        printf("\n");
    }

    

    clock_gettime(CLOCK_REALTIME, &begin);

    
    mkfifo(FIFONAME1, 0666);

    
    int response;
    int index = 0;
    int fd;

    // while (index < 50) {

    //     fd_write = open(FIFONAME1, O_WRONLY);
    //     if (fd_write == -1) {
    //         perror("Problem in opening writing FIFO in P1.");
    //         exit(1);
    //     }

    //     for (int i = index; i < index+4; i++) {
    //         write(fd_write, str[i], strlen(str[i]));
    //     }
    //     close(fd_write);


    //     fd_read = open(FIFONAME2, O_RDONLY);
    //     char ch_id_received[4];
    //     int response2 = read(fd_read, ch_id_received, 4);

    //     if (response2 == -1) {
    //         perror("Problem in reading from reading FIFO in P1.");
    //         exit(1);
    //     }

    //     int max_id_received = ch_id_received[0];
    //     printf("Max ID received by P2 : %d\n", max_id_received);
    //     index++;
    //     close(fd_read);
    // }

    while(1) {
        fd = open(FIFONAME1, O_WRONLY);

        write(fd, str[index], 50);

        close(fd);

        fd = open(FIFONAME1, O_RDONLY);

        read(fd, buf, 50);

        printf("Max index received by P2: %d\n", buf[0]);
        int id = buf[0];

        close(fd);

        if (id >= 50) {
            
            break;
        }

        index = id;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    double time = (double) (end.tv_sec - begin.tv_sec) + (double) (end.tv_nsec - begin.tv_nsec) / (double) 1000000000;
    printf("Time taken : %f\n", time);

}