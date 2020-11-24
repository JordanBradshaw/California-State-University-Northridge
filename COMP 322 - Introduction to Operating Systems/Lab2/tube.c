#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "unistd.h"
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int convertByte2Bit(int tempByte) {//BIT SHIFT TO GET VALUE
    return ((tempByte>>0)&1);
}
int main(int argc, char** argv) {
    int childStatusA=3;
    int childStatusB=3;
    pid_t wPIDA, wPIDB;
    char buffer;
    int pipeA[2];
    int cVar=0;
    //printf("%s\n", argv[3]);
    for (int c=1; c<argc; c++) {
        if (strcmp(argv[c], ",")==0) {
            cVar=c;
            break;
        }
    }
    char* argVar1[cVar];
    char* filteredArgA[cVar-2];
    int l=0;
    for (int b=0; b<cVar-1; b++) {
        argVar1[b]=argv[b+1];
        l++;
    }
    argVar1[l]=NULL;
    char* argVar2[argc-cVar];
    char* filteredArgB[argc-cVar-2];
    int j=0;
    for (int k=cVar+1; k<argc; k++) {
        argVar2[j]=argv[k];
        j++;
    }
    argVar2[j]=NULL;
    char* newenv[]={ NULL };
    if (pipe(pipeA)==-1) {
        perror("Building pipes failed");
        exit(EXIT_FAILURE);
    }
    for (int q=1; q<(cVar-1); q++) {
        filteredArgA[q-1]=argVar1[q];
    }
    filteredArgA[cVar-1]=NULL;
    for (int w=1; w<(argc-cVar-1); w++) {
        filteredArgB[w-1]=argVar2[w];
    }
    filteredArgB[argc-cVar-2]=NULL;
    for (int p=0; p<argc; p++) {
    }
    pid_t pidA=fork();
    if (pidA==0) {//childA
        close(pipeA[0]); //CLOSE READ
        dup2(pipeA[1], STDOUT_FILENO); //DUP WRITE OF PIPE TO STDOUT
        execve(argVar1[0], argVar1, newenv);
        printf("This is line 1st line\n");
        printf("This is line Second line\n");
        exit(0); //CLOSE WHEN FINISHED
    }
    else if (pidA>0) {
        pid_t pidB=fork();
        if (pidB==0) {//childB
            close(pipeA[1]); //CLOSE WRITING
            dup2(pipeA[0], STDIN_FILENO); //DUP READ TO PIPE TO STDIN
            execve(argVar2[0], argVar2, newenv);
            exit(0);
        }
        if (pidB>0) {
            fprintf(stderr, "Child A: PID: %d\n", pidA);
            fprintf(stderr, "Child B: PID: %d\n", pidB);
            close(pipeA[0]); //CLOSE READING END PIPEA
            close(pipeA[1]); //CLOSE WRITING END PIPEA
            wait(&childStatusA);
            wPIDA=waitpid(pidA, &childStatusA, WUNTRACED); //WAIT FOR CHILD PROCESS A TO STOP
            wPIDB=waitpid(pidB, &childStatusB, WUNTRACED); //WAIT FOR CHILD PROCESS B TO STOP
            int exitStatusA=WEXITSTATUS(childStatusA);
            int exitStatusB=WEXITSTATUS(childStatusB);
            fprintf(stderr, "Exit Status A:%d\n", convertByte2Bit(exitStatusA));
            fprintf(stderr, "Exit Status B:%d\n", convertByte2Bit(exitStatusB));
            exit(0);
        }
    }
    return (EXIT_FAILURE);
}

