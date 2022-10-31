#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> // for wait()
#include <sys/types.h> // for pid_t
#include<unistd.h> // for sys calls
#include<string.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    struct dirent *f;
    DIR *dir = NULL;
    if (argc == 1){
        dir = opendir(".");
        if (!dir){
            if (errno == ENOENT){
                printf("Error: this directory does not exist.\n");
                return 0; // should this be 1?
            }
            else {
                printf("Error: can't open this directory.\n");
                return 0; // should this be 1?
            }
            //exit(EXIT_FAILURE);
        }

        while ((f = readdir(dir)) != NULL)
        {
            if (f->d_name[0] == '.') continue;
            printf("%s\t\t", f->d_name);
        }
        printf("\n");
    }

    else if (argc == 2){
        if (strcmp(argv[1], "-a") == 0){
            dir = opendir(".");
            if (!dir){
                if (errno == ENOENT){
                    printf("Error: this directory does not exist.\n");
                    return 0; // should this be 1?
                }
                else {
                    printf("Error: can't open this directory.\n");
                    return 0; // should this be 1?
                }
                //exit(EXIT_FAILURE);
            }

            while ((f = readdir(dir)) != NULL)
            {
                printf("%s\t\t", f->d_name);
            }
            printf("\n");
        }

        else if (strcmp(argv[1], "-i") == 0){
            dir = opendir(".");
            if (!dir){
                if (errno == ENOENT){
                    printf("Error: this directory does not exist.\n");
                    return 0; // should this be 1?
                }
                else {
                    printf("Error: can't open this directory.\n");
                    return 0; // should this be 1?
                }
                //exit(EXIT_FAILURE);
            }

            while ((f = readdir(dir)) != NULL)
            {
                if (f->d_name[0] == '.'){
                    continue;
                }
                printf("%llu\t%s\n", f->d_ino, f->d_name);
            }
        }

        else if ((strcmp(argv[1], "-ia") == 0) || (strcmp(argv[1], "-ai") == 0)){
            dir = opendir(".");
            if (!dir){
                if (errno == ENOENT){
                    printf("Error: this directory does not exist.\n");
                    return 0; // should this be 1?
                }
                else {
                    printf("Error: can't open this directory.\n");
                    return 0; // should this be 1?
                }
                //exit(EXIT_FAILURE);
            }

            while ((f = readdir(dir)) != NULL)
            {
                printf("%llu\t%s\n", f->d_ino, f->d_name);
            }
        }

        /* TODO ls <PATH> */
        else {
            dir = opendir(argv[1]);
            if (!dir){
                if (errno == ENOENT){
                    printf("Error: this directory does not exist.\n");
                    return 0; // should this be 1?
                }
                else {
                    printf("Error: can't open this directory.\n");
                    return 0; // should this be 1?
                }
                //exit(EXIT_FAILURE);
            }

            while ((f = readdir(dir)) != NULL)
            {
                if (f->d_name[0] == '.') continue;
                printf("%s\t\t", f->d_name);
            }
            printf("\n");
        }


    } else if (strcmp(argv[1], "-a") == 0){
        for (int i = 2; i < argc; i++){
            dir = opendir(argv[i]);
            if (!dir){
                if (errno == ENOENT){
                    printf("Error: this directory does not exist.\n");
                    continue;
                }
                else {
                    printf("Error: can't open this directory.\n");
                    continue;
                }
                //exit(EXIT_FAILURE);
            }
            printf("%s:\n", argv[i]);

            while ((f = readdir(dir)) != NULL)
            {
                printf("%s\t\t", f->d_name);
            }
            printf("\n\n");
        }
    }

    else if (strcmp(argv[1], "-i") == 0) {
        for (int i = 2; i < argc; i++){
            dir = opendir(argv[i]);
            if (!dir){
                if (errno == ENOENT){
                    printf("Error: this directory does not exist.\n");
                    continue;
                }
                else {
                    printf("Error: can't open this directory.\n");
                    continue;
                }
                //exit(EXIT_FAILURE);
            }
            printf("%s:\n", argv[i]);
            while ((f = readdir(dir)) != NULL)
            {
                if (f->d_name[0] == '.'){
                    continue;
                }
                printf("%llu\t%s\n", f->d_ino, f->d_name);
            }
            printf("\n");
        }
    }

    else if ((strcmp(argv[1], "-ia") == 0) || (strcmp(argv[1], "-ai") == 0)) {
        for (int i = 2; i < argc; i++){
            dir = opendir(argv[i]);
            if (!dir){
                if (errno == ENOENT){
                    printf("Error: this directory does not exist.\n");
                    continue;
                }
                else {
                    printf("Error: can't open this directory.\n");
                    continue;
                }
                //exit(EXIT_FAILURE);
            }
            printf("%s:\n", argv[i]);

            while ((f = readdir(dir)) != NULL)
            {
                printf("%llu\t%s\n", f->d_ino, f->d_name);
            }
            printf("\n");
        }
    }

    else {
        for (int i = 1; i < argc; i++){
            dir = opendir(argv[i]);
            if (!dir){
                if (errno == ENOENT){
                    printf("Error: this directory does not exist.\n");
                    continue;
                }
                else {
                    printf("Error: can't open this directory.\n");
                    continue;
                }
                //exit(EXIT_FAILURE);
            }
            printf("%s:\n", argv[i]);

            while ((f = readdir(dir)) != NULL)
            {
                printf("%s\t\t", f->d_name);
            }
            printf("\n\n");
        }
    }

}