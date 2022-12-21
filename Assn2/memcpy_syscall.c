#include <linux/kernel.h>
#include <linux/syscalls.h>


SYSCALL_DEFINE4(kernel_2d_memcpy, int*, source, int*, destination, int, size_1, int, size_2)
{
    float buffer[8][8]; 
    
    if (__copy_from_user(buffer, source, sizeof(int)*(size_1)*(size_2))) return -EFAULT;
    if (__copy_to_user(destination, buffer, sizeof(int)*(size_1)*(size_2))) return -EFAULT;

    return 0;
}