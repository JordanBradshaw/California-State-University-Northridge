/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: yups
 *
 * Created on May 1, 2020, 4:02 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>   /* umask() */
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
static pid_t mole1;
static pid_t mole2;
static int num;
char path[900];
char molePath[1024];


static void usrHandler(int signum) {
    srand(time(NULL)); ///<~~~~ THIS IS WHY rand() was always returning 1
    char mNum[30];
    num = rand() % 2; /////////////////////RANDOM DEPENDING
    snprintf(molePath,1024, "%s/mole", path);
    snprintf(mNum, 2, "%d", num + 1);
    char *mArgv[] = {molePath, mNum, path, NULL};
    if (signum == SIGUSR1){//////kill child process #1 (mole1)
           if(mole1){
            kill(mole1, SIGKILL);}
        if ((mole1 = fork())== 0) {
            execv(mArgv[0], mArgv);
            while(1);}
        signal(SIGUSR1, usrHandler);}
    else if (signum == SIGUSR2) {//Upon SIG_USER2, the program will
       if (mole2){
       kill(mole2, SIGKILL);}//////kill child process #2 (mole2)
        if ((mole2 = fork())== 0) {
           execv(mArgv[0], mArgv);}
        signal(SIGUSR2, usrHandler);
        while(1);}
}

static void termHandler(int signum) {
    if (signum == SIGTERM) {
        kill(mole1, SIGTERM);
        kill(mole2, SIGTERM);
        exit(0);
    }}
    int main(int argc, char **argv) {
        pid_t daemonPID;
        pid_t sid;
        if ((daemonPID = fork()) < 0){
        fprintf(stderr, "fork() failed\n");
        }
        if (daemonPID != 0) {
            // Kill parent so daempn runs in background
            fprintf(stderr, "Daemon PID: %d\n", daemonPID);
            exit(0);
        }
        if (daemonPID == 0) {
            getcwd(path, sizeof (path));
            signal(SIGTERM, termHandler); //REDIRECT SIGNALS TO HANDLER
            signal(SIGUSR1, usrHandler);
            signal(SIGUSR2, usrHandler);
            umask(0); //Change file permissions of daemon
            if ((sid = setsid()) < 0) //make daemon session leader
                fprintf(stderr, "setsid() failed\n");
            int fd1 = open("/dev/null", O_RDONLY);
            //if (chdir("/") != 0) //CHANGE DIRECTORY TO ROOT
            if (fd1 < 0) //ERROR
                fprintf(stderr, "failed to open log\n");
            if (dup2(fd1, STDOUT_FILENO) < 0) //REDIRECT STDOUT TO LOG FILE
                fprintf(stderr, "redirect STDOUT failed");
            if (dup2(fd1, STDERR_FILENO) < 0) //REDIRECT STDERR TO LOG FILE
                fprintf(stderr, "redirect STDERR failed\n");
            if (dup2(fd1, STDIN_FILENO) < 0)
                fprintf(stderr, "redirect STDIN failed\n");
            close(fd1); //CLOSE FILE
            while (1) {
                sleep(1);
                //fputs("s", fp);
            }
        }

        return (0);
    }

