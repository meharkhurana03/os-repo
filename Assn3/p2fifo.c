#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


#define BUFFERSIZE 200
#define FIFONAME1 "myFIFO1"
#define FIFONAME2 "myFIFO2"


int main() {
    char buf[BUFFERSIZE];

    int fd_write, fd_read;
    mkfifo(FIFONAME1, 0666);
    mkfifo(FIFONAME2, 0666);

    int max_id_received = 0;

    int i = 0;

    sleep(1);
    printf("hello from p2\n");

    while (1) {

        while (i < max_id_received + 5) {
            fd_read = open(FIFONAME1, O_RDONLY);
            int response = read(fd_read, buf, BUFFERSIZE);
            close(fd_read);

            if (response < 0) {
                perror("Problem reading from reading FIFO in P2");
                exit(1);
            }

            i = buf[0];

            printf("String received in P2 : ");
            for (int j = 0; j<9; j++) {
                printf("%c", buf[j]);
            }
            printf("\n");

            printf("ID received in P2 : %d", buf[0]);
        }

        max_id_received = i;
        sprintf(buf, "%d", max_id_received);
        fd_write = open(FIFONAME2, O_WRONLY);
        int response = write(fd_write, buf, BUFFERSIZE);
        close(fd_write);
        if (response < 0) {
            perror("Problem writing to FIFO in P2");
            exit(1);
        }

        if (max_id_received >= 50) {
            exit(0);
        }
    }


}