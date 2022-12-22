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
    
    mkfifo(FIFONAME1, 0666);

    
    int response;
    int index = 0;
    int fd;
    int this;

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
        fd = open(FIFONAME1, O_RDONLY);

        read(fd, buf, 50);

        for(int i = 0; i < 5; i++) {
            this = buf[i*10];
            printf("P2 %d  : ", this);
            for (int j = 0; j < 8; j++) {
                printf("%c", buf[i*10 + j]);
            }
            printf("\n");
        }

        close(fd);

        fd = open(FIFONAME1, O_WRONLY);

        for (int i = 0; i < 5; i++) {
            if (buf[i*10] > index) {
                index = buf[i*10];
            }
        }
        char out[50];
        memset(out, 50, sizeof(char));
        out[0] = index;

        write(fd, out, 50);

        // printf("Max index received by P2: %d\n", index);

        close(fd);

        if (index >= 50) {
            exit(1);
        }
    }

}