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
#include <fcntl.h>


char wbuffer[1048576] = ""; // 1MB max size
char rbuffer[1048576] = ""; // 1MB max size

int main(int argc, char *argv[]) {
    if (argc < 2){
        printf("Usage: cat [-ne] <file1> ... > <infile>");
        return 0;
    } else {
        if (argc >= 4){
            if (strcmp(argv[argc-2], ">") == 0){
                int f=open(argv[argc-1], O_WRONLY);
                if (f == -1){
                    printf("Cannot open file '%s'.\n", argv[argc-1]);
                    return 0;
                }
                if (strcmp(argv[1], "-n") == 0){
                    int count = 0;
                    for (int i=2; i < argc-2; i++){
                        memset(rbuffer, 0, sizeof(rbuffer));
                        int f2 = open(argv[i], O_RDONLY);
                        if (f2 == -1){
                            printf("Cannot open file '%s'.\n", argv[i]);
                            return 0;
                        }
                        while ((count = read(f2, rbuffer, 1048576)) > 0){
                            strcat(wbuffer, rbuffer);
                        }
                        close(f2);
                    }
                    int ncount = 1;
                    char numbuffer[10];
                    sprintf(numbuffer, "%d  ", ncount);
                    write(f, numbuffer, strlen(numbuffer));
                    // printf("%d  ", ncount);
                    for(int i=0; i<strlen(wbuffer); i++){
                        char c[2];
                        sprintf(c, "%c", wbuffer[i]);
                        write(f, c, 1);
                        // printf("%c", wbuffer[i]);
                        if (wbuffer[i] == '\n'){
                            ncount++;
                            sprintf(numbuffer, "%d  ", ncount);
                            write(f, numbuffer, strlen(numbuffer));
                        }
                    }
                    close(f);
                    return 0;


                } else if (strcmp(argv[1], "-e") == 0){
                    int count = 0;
                    for (int i=2; i < argc-2; i++){
                        memset(rbuffer, 0, sizeof(rbuffer));
                        int f2 = open(argv[i], O_RDONLY);
                        if (f2 == -1){
                            printf("Cannot open file '%s'.\n", argv[i]);
                            return 0;
                        }
                        while ((count = read(f2, rbuffer, 1048576)) > 0){
                            strcat(wbuffer, rbuffer);
                        }
                        close(f2);
                    }
                    int ncount = 1;
                    // char numbuffer[10];
                    char d[2];
                    // sprintf(numbuffer, "%d  ", ncount);
                    sprintf(d, "%c", '$');
                    
                    // printf("%d  ", ncount);
                    for(int i=0; i<strlen(wbuffer); i++){
                        
                        if (wbuffer[i] == '\n'){
                            // printf("%s", d);
                            write(f, d, 1);
                        }
                        char c[2];
                        sprintf(c, "%c", wbuffer[i]);
                        write(f, c, 1);
                        // printf("%c", wbuffer[i]);
                        // if (wbuffer[i] == '\n'){
                        //     ncount++;
                        //     sprintf(numbuffer, "%d  ", ncount);
                        //     write(f, numbuffer, strlen(numbuffer));
                        // }
                    }
                    close(f);
                    return 0;



                } else if (strcmp(argv[1], "-ne") == 0 || strcmp(argv[1], "-en") == 0) {
                    int count = 0;
                    for (int i=2; i < argc-2; i++){
                        memset(rbuffer, 0, sizeof(rbuffer));
                        int f2 = open(argv[i], O_RDONLY);
                        if (f2 == -1){
                            printf("Cannot open file '%s'.\n", argv[i]);
                            return 0;
                        }
                        while ((count = read(f2, rbuffer, 1048576)) > 0){
                            strcat(wbuffer, rbuffer);
                        }
                        close(f2);
                    }
                    int ncount = 1;
                    char numbuffer[10];
                    char d[2];
                    sprintf(numbuffer, "%d  ", ncount);
                    write(f, numbuffer, strlen(numbuffer));
                    sprintf(d, "%c", '$');
                    
                    // printf("%d  ", ncount);
                    for(int i=0; i<strlen(wbuffer); i++){
                        
                        if (wbuffer[i] == '\n'){
                            // printf("%s", d);
                            write(f, d, 1);
                        }
                        char c[2];
                        sprintf(c, "%c", wbuffer[i]);
                        write(f, c, 1);
                        // printf("%c", wbuffer[i]);
                        if (wbuffer[i] == '\n'){
                            ncount++;
                            sprintf(numbuffer, "%d  ", ncount);
                            write(f, numbuffer, strlen(numbuffer));
                        }
                    }
                    close(f);
                    return 0;

                }
                int count = 0;
                for (int i=1; i < argc-2; i++){
                    memset(rbuffer, 0, sizeof(rbuffer));
                    int f2 = open(argv[i], O_RDONLY);
                    if (f2 == -1){
                        printf("Cannot open file '%s'.\n", argv[i]);
                        return 0;
                    }
                    while ((count = read(f2, rbuffer, 1048576)) > 0){
                        strcat(wbuffer, rbuffer);
                    }
                    close(f2);
                }
                write(f,wbuffer,strlen(wbuffer));
                close(f);
            }


            else {
                // argc>=4 but no infile
                if (strcmp(argv[1], "-n") == 0){
                    int count = 0;
                    for (int i=2; i < argc; i++){
                        memset(rbuffer, 0, sizeof(rbuffer));
                        int f2 = open(argv[i], O_RDONLY);
                        if (f2 == -1){
                            printf("Cannot open file '%s'.\n", argv[i]);
                            return 0;
                        }
                        while ((count = read(f2, rbuffer, 1048576)) > 0){
                            strcat(wbuffer, rbuffer);
                        }
                        close(f2);
                    }
                    int ncount = 1;
                    printf("%d  ", ncount);
                    for(int i=0; i<strlen(wbuffer); i++){
                        printf("%c", wbuffer[i]);
                        if (wbuffer[i] == '\n'){
                            ncount++;
                            printf("%d  ", ncount);
                        }
                    }
                    printf("\n");
                    return 0;


                } else if (strcmp(argv[1], "-e") == 0){
                    int count = 0;
                    for (int i=2; i < argc; i++){
                        memset(rbuffer, 0, sizeof(rbuffer));
                        int f2 = open(argv[i], O_RDONLY);
                        if (f2 == -1){
                            printf("Cannot open file '%s'.\n", argv[i]);
                            return 0;
                        }
                        while ((count = read(f2, rbuffer, 1048576)) > 0){
                            strcat(wbuffer, rbuffer);
                        }
                        close(f2);
                    }
                    int ncount = 1;
                    // printf("%d  ", ncount);
                    for(int i=0; i<strlen(wbuffer); i++){
                        if (wbuffer[i] == '\n') printf("$");
                        printf("%c", wbuffer[i]);
                        // if (wbuffer[i] == '\n'){
                        //     ncount++;
                        //     printf("%d  ", ncount);
                        // }
                    }
                    printf("\n");
                    return 0;


                } else if (strcmp(argv[1], "-ne") == 0 || strcmp(argv[1], "-en") == 0) {
                    int count = 0;
                    for (int i=2; i < argc; i++){
                        memset(rbuffer, 0, sizeof(rbuffer));
                        int f2 = open(argv[i], O_RDONLY);
                        if (f2 == -1){
                            printf("Cannot open file '%s'.\n", argv[i]);
                            return 0;
                        }
                        while ((count = read(f2, rbuffer, 1048576)) > 0){
                            strcat(wbuffer, rbuffer);
                        }
                        close(f2);
                    }
                    int ncount = 1;
                    printf("%d  ", ncount);
                    for(int i=0; i<strlen(wbuffer); i++){
                        if (wbuffer[i] == '\n') printf("$");
                        printf("%c", wbuffer[i]);
                        if (wbuffer[i] == '\n'){
                            ncount++;
                            printf("%d  ", ncount);
                        }
                    }
                    printf("\n");
                    return 0;

                }
                int count = 0;
                for (int i=1; i < argc; i++){
                    memset(rbuffer, 0, sizeof(rbuffer));
                    int f2 = open(argv[i], O_RDONLY);
                    // printf("%s\n",argv[i]);
                    if (f2 == -1){
                        printf("Cannot open file '%s'.\n", argv[i]);
                        return 0;
                    }
                    while ((count = read(f2, rbuffer, 1048576)) > 0){
                        strcat(wbuffer, rbuffer);
                    }
                    close(f2);
                    strcpy(rbuffer, "");
                }
                // printf("<<<THIS IS >=4 AND NO INFILE\n");
                printf("%s\n", wbuffer);
                // printf("<<<THIS IS >=4 AND NO INFILE>>>\n");
            }
        }
        else if (argc == 3) {
            if (strcmp(argv[1], "-n") == 0){
                memset(rbuffer, 0, sizeof(rbuffer));
                int count = 0;
                int f2 = open(argv[2], O_RDONLY);
                if (f2 == -1){
                    printf("Cannot open file '%s'.\n", argv[2]);
                    return 0;
                }
                while ((count = read(f2, rbuffer, 1048576)) > 0){
                    strcat(wbuffer, rbuffer);
                }
                close(f2);
                int ncount = 1;
                printf("%d  ", ncount);
                for(int i=0; i<strlen(wbuffer); i++){
                    printf("%c", wbuffer[i]);
                    if (wbuffer[i] == '\n'){
                        ncount++;
                        printf("%d  ", ncount);
                    }
                }
                printf("\n");
                // printf("%s\n", wbuffer);
                return 0;


            } else if (strcmp(argv[1], "-e") == 0){
                memset(rbuffer, 0, sizeof(rbuffer));
                int count = 0;
                int f2 = open(argv[2], O_RDONLY);
                if (f2 == -1){
                    printf("Cannot open file '%s'.\n", argv[2]);
                    return 0;
                }
                while ((count = read(f2, rbuffer, 1048576)) > 0){
                    strcat(wbuffer, rbuffer);
                }
                close(f2);
                int ncount = 1;
                // printf("%d  ", ncount);
                for(int i=0; i<strlen(wbuffer); i++){
                    if (wbuffer[i] == '\n') printf("$");
                    printf("%c", wbuffer[i]);
                    // if (wbuffer[i] == '\n'){
                    //     ncount++;
                    //     printf("%d  ", ncount);
                    // }
                }
                printf("\n");
                // printf("%s\n", wbuffer);
                return 0;


            } else if (strcmp(argv[1], "-ne") == 0 || strcmp(argv[1], "-en") == 0){
                memset(rbuffer, 0, sizeof(rbuffer));
                int count = 0;
                int f2 = open(argv[2], O_RDONLY);
                if (f2 == -1){
                    printf("Cannot open file '%s'.\n", argv[2]);
                    return 0;
                }
                while ((count = read(f2, rbuffer, 1048576)) > 0){
                    strcat(wbuffer, rbuffer);
                }
                close(f2);
                int ncount = 1;
                printf("%d  ", ncount);
                for(int i=0; i<strlen(wbuffer); i++){
                    if (wbuffer[i] == '\n') printf("$");
                    printf("%c", wbuffer[i]);
                    if (wbuffer[i] == '\n'){
                        ncount++;
                        printf("%d  ", ncount);
                    }
                }
                printf("\n");
                // printf("%s\n", wbuffer);
                return 0;

            }
            else {
                // 2 files input
                memset(rbuffer, 0, sizeof(rbuffer));
                int count = 0;
                int f2 = open(argv[1], O_RDONLY);
                if (f2 == -1){
                    printf("Cannot open file '%s'.\n", argv[1]);
                    return 0;
                }
                while ((count = read(f2, rbuffer, 1048576)) > 0){
                    strcat(wbuffer, rbuffer);
                }
                close(f2);
                memset(rbuffer, 0, sizeof(rbuffer));
                int f3 = open(argv[2], O_RDONLY);
                if (f3 == -1){
                    printf("Cannot open file '%s'.\n", argv[2]);
                    return 0;
                }
                while ((count = read(f3, rbuffer, 1048576)) > 0){
                    strcat(wbuffer, rbuffer);
                }
                close(f3);
                printf("%s\n", wbuffer);
                return 0;
            }
            
        } else {
            int count = 0;
            int f2 = open(argv[1], O_RDONLY);
            if (f2 == -1){
                printf("Cannot open file '%s'.\n", argv[1]);
                return 0;
            }
            while ((count = read(f2, rbuffer, 1048576)) > 0){
                strcat(wbuffer, rbuffer);
            }
            close(f2);
            printf("%s\n", wbuffer);
            return 0;
        }
    }
}