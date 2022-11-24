#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <errno.h>
#include <linux/kernel.h>

#define TWOD_MEMCPY_SYSCALL 451



int main()
{
    float test[5][3] = {{1.1, 2.2, 3.3}, {4.4 ,5.5, 6.6}, {7,8,9}, {3, 2, 1}, {3, 3, 3}};
    float response[5][3];

    long sys_call_status;
    sys_call_status = syscall(TWOD_MEMCPY_SYSCALL, test, response, 5, 3);

    if (sys_call_status != EFAULT)
    {
        printf("\nkernel_2d_memcpy invoked successfully.\n\n");
        
        printf("Array sent:\n");
        for (int i=0; i<5; i++) {
            for (int j=0; j<3; j++) {
                printf("%f ", test[i][j]);
            }
            printf("\n");
        }
        printf("\n");

        printf("Array received:\n");
        for(int i=0; i<5; i++){
            for(int j=0; j<3; j++){
                printf("%f ", response[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}