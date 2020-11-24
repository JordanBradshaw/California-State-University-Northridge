#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "unistd.h"
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

convertByte2Bit(int tempByte) {//BIT SHIFT TO GET VALUE
    return ((tempByte>>0)&1);
}
int main(int argc, char** argv) {
    char* newArg[argc];
    char* newFilteredArg[argc-1];
    for (int i=1; i<argc; i++) {
        newArg[i-1]=argv[i];
    }
    for (int i=1; i<(argc-1); i++) {
        newFilteredArg[i-1]=newArg[i];
    }
    char FILELOCATION1=newArg[0];
    for (int i=0; i<=argc; i++) {
    }
    newFilteredArg[argc-1]=NULL;
    pid_t pid=fork(); //FORK AND DECLARE VARS
    int childStatus=-1;
    pid_t wPID;
    bool validPID=(pid>=0)?true:false;
    if (validPID==true) {
        if (pid==0) {//PID RETURNS 0 IF IN CHILD
            int i, k=0;
            for (i=1; i<argc; i++) {
                newArg[k]=argv[i];
                k++;
            }
            newArg[k]=NULL;
            const char* filename="/bin/ls";
            char* newargv[]={ "/bin/ls","-t", NULL };
            char* newenviron[]={ NULL };
            newargv[0]=argv[1];
            if (execve(newArg[0], newArg, newenviron)==-1) {
                printf("Execve Error\n");
            }
            return 1; //CLOSE WHEN FINISHED
        }
        else {//PID RETURNS PID OF CHILD (IN PARENT)
            fprintf(stderr, "Child PID: %d\n", pid);
            wPID=waitpid(pid, &childStatus, WUNTRACED); //WAIT FOR CHILD PROCESS TO STOP
            fprintf(stderr, "Child Return Value: %d\n", convertByte2Bit(childStatus));
        }
    }
    else {//VALID PID == FALSE SO!
        printf("Error Creating Child!");
    }
    return (EXIT_SUCCESS);
}

