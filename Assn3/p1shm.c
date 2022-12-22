#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>


#define MEMSIZE 40*sizeof(char)
// #define MEM2SIZE 2*sizeof(int)
#define BIL 1000000000;

int main() {
    struct timespec t_begin, t_end;

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

    
    
    
    clock_gettime(CLOCK_REALTIME, &t_begin);

    int max_recd = 0;
    while (1) {
        for (int i = max_recd; i < max_recd + 5; i++) {
            int fd = shm_open("/shm", O_WRONLY | O_CREAT, 0666);
            
            if (fd < 0) {
                perror("Problem in creating shm.");
                exit(1);
            }
            ftruncate(fd, MEMSIZE);
            char* mem = (char *) mmap(0, MEMSIZE, PROT_WRITE, MAP_SHARED, fd, 0);

            sprintf(mem, "%s", str[i]);

            munmap(mem, MEMSIZE);
            close(fd);
        }

        int fd2 = shm_open("/shm", O_RDONLY | O_CREAT, 0666);
        if (fd2 < 0) {
            perror("1Problem in creating shm2.");
            exit(1);
        }
        
        char *val = (char *)mmap(0, MEMSIZE, PROT_READ, MAP_SHARED, fd2, 0);
        while (strlen(val) != 1);
        if (strlen(val) < 5 && val[0] > max_recd) {
            max_recd = val[0];
            printf("Max ID received by P2 : %d\n", max_recd);
        }
        munmap(val, MEMSIZE);
        close(fd2);
        


        if (max_recd >= 50) {
            clock_gettime(CLOCK_REALTIME, &t_end);
            double time = (double) (t_end.tv_sec - t_begin.tv_sec) + (t_end.tv_nsec - t_begin.tv_nsec) / (double) BIL;
            printf("Time taken : %f\n", time);
            shm_unlink("shm");
            exit(0);
        }

    }
}