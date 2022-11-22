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
    if (argc < 2) {
        printf("Incorrect usage of command, mkdir.\n");
        return 0;
    }
    if (argc == 2){
        if (stat(argv[1], &status) == -1) {
            int result = mkdir(argv[1], 0777);
            if (result != 0){
                printf("Could not create '%s'.\n", argv[1]);
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
        if (argv[1][0] == '-' && argv[1][1] == 'm' && argv[1][2] == '=' && strcmp(argv[2], "-v") == 0){
            int mode = 0000;
            if ((strlen(argv[1]) == 6)){
                if (argv[1][3] == 'r') mode += 0444;
                if (argv[1][4] == 'w') mode += 0222;
                if (argv[1][5] == 'x') mode += 0111;
            }
            else {
                printf("Invalid arguments for -m in command, mkdir.\n");
            }

            for (int i = 3; i < argc; i++){
                
                if (stat(argv[i], &status) == -1) {
                    int result = mkdir(argv[i], mode);
                    if (result != 0){
                        printf("Could not create '%s'.\n", argv[i]);
                        return 0;
                    } else {
                        printf("Created directory '%s'.\n", argv[i]);
                        continue;
                    }
                }
                else {
                    printf("Directory '%s' exists.\n", argv[i]);
                }
            }
            printf("Successful.\n");


        }
        else if (argv[1][0] == '-' && argv[1][1] == 'm' && argv[1][2] == '='){
            int mode = 0000;
            if ((strlen(argv[1]) == 6)){
                if (argv[1][3] == 'r') mode += 0444;
                if (argv[1][4] == 'w') mode += 0222;
                if (argv[1][5] == 'x') mode += 0111;
            }
            else {
                printf("Invalid arguments for -m in command, mkdir.\n");
            }

            for (int i = 2; i < argc; i++){
                
                if (stat(argv[i], &status) == -1) {
                    int result = mkdir(argv[i], mode);
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


        } else if (argv[2][0] == '-' && argv[2][1] == 'm' && argv[2][2] == '=' && strcmp(argv[1], "-v") == 0){
            int mode = 0000;
            if ((strlen(argv[2]) == 6)){
                if (argv[2][3] == 'r') mode += 0444;
                if (argv[2][4] == 'w') mode += 0222;
                if (argv[2][5] == 'x') mode += 0111;
            }
            else {
                printf("Invalid arguments for -m in command, mkdir.\n");
            }

            for (int i = 3; i < argc; i++){
                
                if (stat(argv[i], &status) == -1) {
                    int result = mkdir(argv[i], mode);
                    if (result != 0){
                        printf("Could not create '%s'.\n", argv[i]);
                        return 0;
                    } else {
                        printf("Created directory '%s'.\n", argv[i]);
                        continue;
                    }
                }
                else {
                    printf("Directory '%s' exists.\n", argv[i]);
                }
            }
            printf("Successful.\n");
        }
        else if (strcmp(argv[1], "-v") == 0){
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
        else {
            for (int i = 1; i < argc; i++){
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
}