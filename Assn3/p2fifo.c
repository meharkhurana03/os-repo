#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>


#define BUFFERSIZE 10
#define FIFONAME1 "myFIFO1"
#define FIFONAME2 "myFIFO2"


int main() {
    char buf[BUFFERSIZE];

    int fd_write, fd_read;
    mkfifo(FIFONAME1, 0666);
    mkfifo(FIFONAME2, 0666);

    int max_id_received = 0;

    int i = 0;

    // printf("hello from p2\n");
    sleep(0.1);

    while (1) {
        
        while (i < max_id_received + 5) {
            fd_read = open(FIFONAME1, O_RDONLY);
            int response = read(fd_read, buf, BUFFERSIZE);
            

            if (response < 0) {
                perror("Problem reading from reading FIFO in P2");
                exit(1);
            }
            printf("[P2] : ");
            printf("%d ", buf[0]);
            printf("%s", buf+1);
            printf("\n");

            close(fd_read);
        }
        

        max_id_received = i;
        buf[0] = max_id_received;
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