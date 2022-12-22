#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/mman.h>
#include <unistd.h>


#define MEMSIZE 50*sizeof(char)
// #define MEM2SIZE 2*sizeof(int)

int main() {

    int max_recd = 0;
    while (1) {
        for (int i = 0; i < 5; i++) {
            int fd = shm_open("/shm", O_RDONLY | O_CREAT, 0666);
            
            if (fd < 0) {
                perror("Problem in creating shm.");
                exit(1);
            }
            
            char* mem = -1;
            while (mem == -1) {
                mem = (char *) mmap(0, MEMSIZE, PROT_READ, MAP_SHARED, fd, 0);
                // printf("%d\n\n\n", mem);
            }
            int id = mem[0];
            if ( id > max_recd ) max_recd = id;
            printf("P2 %d : %s\n", id, mem);

            munmap(mem, MEMSIZE);
            close(fd);
        }

        int fd2 = shm_open("/shm", O_WRONLY | O_CREAT, 0666);
        if (fd2 < 0) {
            perror("2Problem in creating shm2.");
            exit(1);
        }
        ftruncate(fd2, MEMSIZE);

        char *val = (char *)mmap(0, MEMSIZE, PROT_WRITE, MAP_SHARED, fd2, 0);
        val[0] = max_recd;
        val[1] = '\0';

        munmap(val, MEMSIZE);
        close(fd2);
        


        if (max_recd >= 50) {
            printf("Time taken:");
            shm_unlink("shm");
            exit(0);
        }

    }
}