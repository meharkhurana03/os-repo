#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define SHM_SIZE 3*sizeof(int)

int main()
{
    int fd = shm_open("/meow", O_CREAT | O_EXCL | O_RDWR, 0600);
    if (fd < 0) {
        printf("Error creating shm object\n");
        return EXIT_FAILURE;
    }

    /*Resize the shm*/
    ftruncate(fd, SHM_SIZE );

    int* data = (int*) mmap(0, SHM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

    data[0] = 4;
    data[1] = 8;
    data[2] = 7;

    munmap(data,SHM_SIZE);
    close(fd);
    return EXIT_SUCCESS;
}

    
