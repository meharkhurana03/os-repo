#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#define SNAME "socket"

int main() {
    int s;
    int t;
    int len;
    struct timespec t_begin, t_end;
    struct sockaddr_un remote;
    char str2[100];
    
    char str[50][10];
    for (int i = 0; i < 50; i++) {
        str[i][0] = i + 1;
    }
    for (int i = 0; i < 50; i++) {
		for (int j = 1; j < 9; j++) {
			str[i][j] = rand()%92 + 33;
		}
        str[i][9] = '\0';
	}

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1){
        perror("Problem in creating socket.");
        exit(1);
    }

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SNAME);
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);

    if ( connect(s, (struct sockaddr *)&remote, len) == -1 ) {
        perror("connect");
        exit(1);
    }

    while(printf("> "), fgets(str2, 100, stdin), !feof(stdin)) {
        if (send(s, str2, strlen(str2), 0) == -1) {
            perror("send");
            exit(1);
        }
        if ((t=recv(s, str2, 100, 0)) > 0) {
            str2[t] = '\0';
            printf("echo> %s", str);
        } else {
            if (t < 0) perror("recv");
            else printf("Server closed connection\n");
            exit(1);
        }
    }
}