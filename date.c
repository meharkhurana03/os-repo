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


int main(int argc, char *argv[]) {
    time_t t = time(NULL);
    struct tm thistime = *localtime(&t);
    struct tm utctime = *gmtime(&t);
    if (argc == 1){
        // printf("%s", ctime(&thistime));
        printf("Local Time: %d-%02d-%02d %02d:%02d:%02d\n", thistime.tm_year + 1900, thistime.tm_mon + 1, thistime.tm_mday, thistime.tm_hour, thistime.tm_min, thistime.tm_sec);
    }

    else if (strcmp(argv[1], "-u") == 0){
        // printf("%s", ctime(&utctime));
        printf("UTC: %d-%02d-%02d %02d:%02d:%02d\n", utctime.tm_year + 1900, utctime.tm_mon + 1, utctime.tm_mday, utctime.tm_hour, utctime.tm_min, utctime.tm_sec);
    }

    else if (strcmp(argv[1], "-r") == 0){
        struct stat f;
        int status = stat(argv[2], &f);
        if (status == -1){
            printf("Cannot open file '%s'.\n", argv[2]);
            return 0;
        }
        printf("File '%s' last modified on: %s", argv[2], ctime(&f.st_mtime));

    }

    else {
        printf("Incorrect use of the command, date.\n");
    }
}