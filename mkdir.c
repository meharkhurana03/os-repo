#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> // for wait()
#include <sys/types.h> // for pid_t
#include<unistd.h> // for sys calls
#include<string.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>
#include <time.h>
#include <sys/stat.h>

char thispath[PATH_MAX];


int main(int argc, char *argv[]) {
    struct stat status = {0};

    if (argc == 2){
        if (stat(argv[1], &status) == -1) {
            int result = mkdir(argv[1], 0777);
            if (result != 0){
                printf("mkdir failed.\n");
                return 0;
            } else {
                printf("Successful.\n");
            }
        }
        else {
            printf("Directory exists.\n");
        }
    }

    else {
        if (strcmp(argv[1], "-v") == 0){
            for (int i = 2; i < argc; i++){
                if (stat(argv[i], &status) == -1) {
                    int result = mkdir(argv[i], 0777);
                    if (result != 0){
                        printf("Could not create '%s'.\n", argv[i]);
                    } else {
                        printf("Created directory '%s'.\n", argv[i]);
                    }
                }
                else {
                    printf("Directory '%s' exists.\n", argv[i]);
                }
            }
            printf("Successful.\n");
        }
        else if (strcmp(argv[1], "-p") == 0){
            for (int i = 2; i < argc; i++){
                int slash = 0;
                while (stat(thispath, &status) == -1){
                    if (argv[i][slash] == '/'){
                        strcpy(thispath, argv[i]);
                    }
                }
                if (stat(argv[i], &status) == -1) {
                    int result = mkdir(argv[i], 0777);
                    if (result != 0){
                        printf("Could not create '%s'.\n", argv[i]);
                        return 0;
                    } else {
                        continue;
                    }
                }
                else {
                    printf("Directory '%s' exists.\n", argv[i]);
                }
            }
            printf("Successful.\n");
        }
    }

    
//         else if (strcmp(argv[1], "-f") == 0){
//             for (int i = 2; i < argc; i++){
//                 status = remove(argv[i]);
//                 if (status != 0){
//                     continue;
//                 }
//                 else {
//                     continue;
//                 }
//             }
//             printf("Successful.\n");
//         }
//         else if ((strcmp(argv[1], "-vf") == 0) || (strcmp(argv[1], "-fv") == 0)){
//             for (int i = 2; i < argc; i++){
//                 status = remove(argv[i]);
//                 if (status != 0){
//                     continue;
//                 }
//                 else {
//                     printf("Removed '%s'.\n", argv[i]);
//                 }
//             }
//             printf("Successful.\n");
//         }

//         else {
//             for (int i = 1; i < argc; i++){
//                 status = remove(argv[1]);
//                 if (status != 0){
//                     printf("Could not remove '%s'.\n", argv[1]);
//                 }
//                 else {
//                     continue;
//                 }
//             }
//             printf("Successful.\n");
//         }
//     }
}