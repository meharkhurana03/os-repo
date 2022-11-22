#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> // for wait()
#include <sys/types.h> // for pid_t
#include<unistd.h> // for sys calls
#include<string.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>

// TODO, handle .. and .

int main(int argc, char *argv[]) {
    int status;
    if (argc == 1){
        printf("Usage: rm [-vf] <path> ...\n");
        return 0;
    }
    else if(argc == 2)
    {
        status = remove(argv[1]);
        if (status != 0){
            printf("Could not remove '%s'\n", argv[1]);
        }
        else {
            printf("Successful.\n");
        }
    }

    else {
        if (strcmp(argv[1], "-v") == 0){
            for (int i = 2; i < argc; i++){
                status = remove(argv[i]);
                if (status != 0){
                    printf("Could not remove %s\n", argv[i]);
                }
                else {
                    printf("Removed '%s'\n", argv[i]);
                }
            }
            printf("Successful.\n");
        }
        else if (strcmp(argv[1], "-f") == 0){
            for (int i = 2; i < argc; i++){
                status = remove(argv[i]);
                if (status != 0){
                    continue;
                }
                else {
                    continue;
                }
            }
            printf("Successful.\n");
        }
        else if ((strcmp(argv[1], "-vf") == 0) || (strcmp(argv[1], "-fv") == 0)){
            for (int i = 2; i < argc; i++){
                status = remove(argv[i]);
                if (status != 0){
                    continue;
                }
                else {
                    printf("Removed '%s'\n", argv[i]);
                }
            }
            printf("Successful.\n");
        }

        else {
            for (int i = 1; i < argc; i++){
                status = remove(argv[1]);
                if (status != 0){
                    printf("Could not remove '%s'\n", argv[1]);
                }
                else {
                    continue;
                }
            }
            printf("Successful.\n");
        }
    }
}