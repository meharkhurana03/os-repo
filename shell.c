#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h> // for wait()
#include <sys/types.h> // for pid_t
#include<unistd.h> // for sys calls
#include<string.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>
#include <pthread.h>


char *user;
char host[128];
char cwd[PATH_MAX];
char owd[PATH_MAX];
char this_dir[PATH_MAX];
void shell(int signum);

static void trunc_end(char* s)
{
	char* tmp= strchr(s, '\0');
	tmp= tmp-1;
	if(strcmp(tmp," ")==0)
	{
		*tmp= '\0';
		trunc_end(s);
	}
}





int main(){
	printf("Hello, World! Welcome to SeaShell\n");
    printf("Type 'exit' to exit SeaShell\n");

	signal(SIGINT, shell);
	shell(0);
	return 0;
}


int main2() {
    pid_t pid;

    pid = fork();
    printf ("My pid=%jd\n", (intmax_t) getpid ());
    printf ("Parent's pid=%jd\n", (intmax_t) getppid ());
    if (pid < 0) {
        fprintf(stderr, "Error occurred while attempting to fork.");
        return 1;
    } else if (pid > 0) {
        wait(NULL);
        printf("Child complete.");
    } else {
        execlp("/bin/ls", "ls", NULL);

    }

    return 0;
}

void shell(int signum)
{
		char command[256];
		int flag=1;
        user = getlogin();
        gethostname(host, 128);
        pid_t pid;
        pthread_t ptid;
        if (getcwd(this_dir, sizeof(this_dir)) == NULL){
            perror("Error getting cwd.");
        }

        do{
            if (getcwd(cwd, sizeof(cwd)) == NULL){
                perror("Error getting cwd.");
            }
            printf("%s@%s:%s>>\n$ ", user, host, cwd);

            // scans everything that is not a newline
            scanf("%[^\n]", command);
            // discards the newline
            scanf("%*c");

            trunc_end(command);

            int arglen = 1;
            for(int i=0; i<strlen(command); i++){
                if (command[i]==' '){
                    arglen++;
                }
            }

            char args[arglen][128]; //128 = maxlength of 1 arg

            
            char *s = command, *sep;


            // printf("Original string: '%s'\n", getenv("HOME"));
            // printf("Original string: '%s'\n\n\n",command);

            int iter = 0;
            while( (sep = strsep(&s," ")) != NULL ){
                strcpy(args[iter], sep);
                // printf("%c\n", sep[0]);
                // printf("%s\n", args[iter]);
                // printf("%c\n", s[0]);
                iter++;
            }

            /* EXIT */
            if(strcmp(args[0], "exit") == 0){
                exit(0);
            }

            /* CD */
            else if(strcmp(args[0], "cd") == 0){
                if (arglen == 1) {
                    chdir("/");
                } else if (strcmp(args[1], "-") == 0){
                    chdir(owd);
                } else if (strcmp(args[1], "~") == 0){
                    chdir(getenv("HOME"));
                } else {
                    chdir(args[1]);
                }
                strcpy(owd, cwd);
                if (getcwd(cwd, sizeof(cwd)) == NULL){
                    perror("Error getting cwd.");
                }
            }

            /* ECHO */
            else if (strcmp(args[0], "echo") == 0){
                if (arglen == 1){ // edge case 1
                    printf("\n");

                    // TODO
                } else if (args[1][0] == '-'){
                    if (strlen(args[1]) == 2 && args[1][1] == 'n'){
                        continue;
                    } else if (strlen(args[1]) == 2 && strcmp(args[1], "--help")){
                        continue;
                    }
                } else if (args[1][0] == '$'){ // edge case 2
                    char env[strlen(args[1])];
                    for (int i=1; i < strlen(args[1]); i++){
                        env[i-1] = args[1][i];
                    }
                    env[strlen(env) - 1] = '\0';
                    // printf("%s\n", env);
                    printf("%s\n\n", getenv(env));
                } else {
                    for (int i=0; i<arglen-1;i++){
                        printf("%s ", args[i+1]);
                    }
                    printf("\n");
                }
            }

            /* PWD */
            else if (strcmp(args[0], "pwd") == 0){ // assumption - default is symbolic path
                if (arglen == 1) printf("%s", cwd);

                // TODO
                else if (args[1][0] == '-'){
                    if (args[1][1] == 'L'){ // doesn't matter what is after this, handled error
                        continue;
                    } else if (args[1][1] == 'P'){ // get real path
                        continue;
                    } else {
                        printf("Incorrect use of the command, pwd.\n"); // handled another edge case
                    }
                }
            }

            /* DATE */
            else if (strcmp(args[0], "date") == 0){
                pid = fork();
                if (pid < 0) {
                    fprintf(stderr, "Error occurred while attempting to fork.\n");
                    exit(1);
                } else if (pid > 0) {
                    printf("In parent, waiting for child.\n");
                    wait(NULL);
                } else {
                    printf("In child.\n");
                    char epath[PATH_MAX];
                    strcpy(epath, this_dir);
                    strcat(epath, "/date"); // TODO - handle the case where len > PATH_MAX
                    char *eargs[arglen];
                    char *thisarg;
                    for (int i = 0; i < arglen; i++) {
                        thisarg = strdup(args[i]);
                        eargs[i] = thisarg;
                        // printf("%s\n", args[i]);
                        // printf("%s\n", thisarg);
                        // printf("%s\n", eargs[i]);
                    }
                    // printf("%s\n", eargs[1]);
                    eargs[arglen] = NULL;
                    execvp(epath, eargs);
                }
            }

            /* LS */
            else if (strcmp(args[0], "ls") == 0){
                pid = fork();
                if (pid < 0) {
                    fprintf(stderr, "Error occurred while attempting to fork.\n");
                    exit(1);
                } else if (pid > 0) {
                    printf("In parent, waiting for child.\n");
                    wait(NULL);
                } else {
                    printf("In child.\n");
                    char epath[PATH_MAX];
                    strcpy(epath, this_dir);
                    strcat(epath, "/ls"); // TODO - handle the case where len > PATH_MAX
                    char *eargs[arglen];
                    char *thisarg;
                    for (int i = 0; i < arglen; i++) {
                        thisarg = strdup(args[i]);
                        eargs[i] = thisarg;
                        // printf("%s\n", args[i]);
                        // printf("%s\n", thisarg);
                        // printf("%s\n", eargs[i]);
                    }
                    // printf("%s\n", eargs[1]);
                    eargs[arglen] = NULL;
                    execvp(epath, eargs);
                }
            }

            /* RM */
            else if (strcmp(args[0], "rm") == 0){
                pid = fork();
                if (pid < 0) {
                    fprintf(stderr, "Error occurred while attempting to fork.\n");
                    exit(1);
                } else if (pid > 0) {
                    printf("In parent, waiting for child.\n");
                    wait(NULL);
                } else {
                    printf("In child.\n");
                    char epath[PATH_MAX];
                    strcpy(epath, this_dir);
                    strcat(epath, "/rm"); // TODO - handle the case where len > PATH_MAX
                    char *eargs[arglen];
                    char *thisarg;
                    for (int i = 0; i < arglen; i++) {
                        thisarg = strdup(args[i]);
                        eargs[i] = thisarg;
                        // printf("%s\n", args[i]);
                        // printf("%s\n", thisarg);
                        // printf("%s\n", eargs[i]);
                    }
                    // printf("%s\n", eargs[1]);
                    eargs[arglen] = NULL;
                    execvp(epath, eargs);
                }
            }

            /* MKDIR */
            else if (strcmp(args[0], "mkdir") == 0){
                pid = fork();
                if (pid < 0) {
                    fprintf(stderr, "Error occurred while attempting to fork.\n");
                    exit(1);
                } else if (pid > 0) {
                    printf("In parent, waiting for child.\n");
                    wait(NULL);
                } else {
                    printf("In child.\n");
                    char epath[PATH_MAX];
                    strcpy(epath, this_dir);
                    strcat(epath, "/mkdir"); // TODO - handle the case where len > PATH_MAX
                    char *eargs[arglen];
                    char *thisarg;
                    for (int i = 0; i < arglen; i++) {
                        thisarg = strdup(args[i]);
                        eargs[i] = thisarg;
                        // printf("%s\n", args[i]);
                        // printf("%s\n", thisarg);
                        // printf("%s\n", eargs[i]);
                    }
                    // printf("%s\n", eargs[1]);
                    eargs[arglen] = NULL;
                    execvp(epath, eargs);
                }
            }

            /* CAT */
            else if (strcmp(args[0], "cat") == 0){
                pid = fork();
                if (pid < 0) {
                    fprintf(stderr, "Error occurred while attempting to fork.\n");
                    exit(1);
                } else if (pid > 0) {
                    printf("In parent, waiting for child.\n");
                    wait(NULL);
                } else {
                    printf("In child.\n");
                    char epath[PATH_MAX];
                    strcpy(epath, this_dir);
                    strcat(epath, "/cat"); // TODO - handle the case where len > PATH_MAX
                    char *eargs[arglen];
                    char *thisarg;
                    for (int i = 0; i < arglen; i++) {
                        thisarg = strdup(args[i]);
                        eargs[i] = thisarg;
                        // printf("%s\n", args[i]);
                        // printf("%s\n", thisarg);
                        // printf("%s\n", eargs[i]);
                    }
                    // printf("%s\n", eargs[1]);
                    eargs[arglen] = NULL;
                    execvp(epath, eargs);
                }
            }

            else {
                printf("Invalid command, please try again.\n"); // handles spelling mistakes in command name.
            }

        } while (flag == 1);


	// 	do
	// 	{
	// 		printf("$ ");

	// 		scanf("%[^\n]%*c",command);

	// 		removelastspace(command);

	// 		int pipesCount=0;
	// 		for(int i=0;i<strlen(command);i++){
	// 			if(command[i]=='|'){
	// 				pipesCount++;			
	// 			}
	// 		}
	// 		//printf("Number of pipes : %d\n", pipesCount);

	// 		char pipeCommands[pipesCount+1][100];
	// 		int j=0,k=0;
	// 		for(int i=0;i<strlen(command);i++){
	// 			if(command[i]=='|'){
	// 				pipeCommands[j][k-1]='\0';
	// 				j++;
	// 				k=0;									
	// 			}
	// 			else if(command[i]==' '){
	// 				pipeCommands[j][k]='$';
	// 				k++;			
	// 			}
	// 			else{
	// 				pipeCommands[j][k]=command[i];
	// 				k++;
	
	// 			}			
	// 		}
	// 		pipeCommands[j][k]='\0';

	// 		for(int i=0; i<pipesCount+1;i++)			// Loop for each pipe sequence
	// 		{
	// 			//printf("Pipe command : %s\n", pipeCommands[i]);
	// 			char *args[10];	
	// 			int k=0;
	// 			if(i==0){								// First command doesn't has starting symbol $
	// 				args[0]=&pipeCommands[i][0];
	// 				k++;
	// 			}

	// 			unsigned int size=strlen(pipeCommands[i]);
	// 			for(int j=0;j<size;j++)
	// 			{
	// 				if(pipeCommands[i][j]=='$'){
	// 						pipeCommands[i][j]='\0';
	// 						args[k]=&pipeCommands[i][j+1];
	// 						k++;			
	// 				}
	// 			}
	// 			args[k]=NULL;

	// 			if(strcmp(args[0], "exit")==0)
	// 			{
	// 				exit(0);
	// 			}

	// 			pipeSequence(args, pipesCount,k);
	// 			zone++;
	// 		}

	// 		reset();	

	// }while(flag==1);
}