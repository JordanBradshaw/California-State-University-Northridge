/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: yups
 *
 * Created on March 21, 2020, 4:24 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
time_t seconds;
pid_t pid;
void signalHandler(int);
int sigflag;
static int counter = 0;
static int termcounter = 0;

/*int signalReturnVal(char *tempSignal) {
    counter++;
    time(&seconds);
    printf("%s signal received at %ld\n", tempSignal, seconds);
    if (strcmp(tempSignal, "SIGHUP") == 0) {
        return 1;
    }
    if (strcmp(tempSignal, "SIGINT") == 0) {
        return 2;
    }
    if (strcmp(tempSignal, "SIGQUIT") == 0) {
        return 3;
    }
    if (strcmp(tempSignal, "SIGABRT") == 0) {
        return 6;
    }
    if (strcmp(tempSignal, "SIGFPE") == 0) {
        return 8;
    }
    if (strcmp(tempSignal, "SIGKILL") == 0) {
        return 9;
    }
    if (strcmp(tempSignal, "SIGSEGV") == 0) {
        return 11;
    }
    if (strcmp(tempSignal, "SIGPIPE") == 0) {
        return 13;
    }
    if (strcmp(tempSignal, "SIGALRM") == 0) {
        return 14;
    }
    if (strcmp(tempSignal, "SIGTERM") == 0) {
        termcounter++;
        return 15;
    }
    if (strcmp(tempSignal, "SIGUSR1") == 0) {
        return 30;
    }
    if (strcmp(tempSignal, "SIGUSR2") == 0) {
        return 31;
    }
    if (strcmp(tempSignal, "SIGCHLD") == 0) {
        return 20;
    }
    if (strcmp(tempSignal, "SIGCONT") == 0) {
        return 19;
    }
    if (strcmp(tempSignal, "SIGSTOP") == 0) {
        return 17;
    }
    if (strcmp(tempSignal, "SIGTSTP") == 0) {
        return 18;
    }
    if (strcmp(tempSignal, "SIGTTIN") == 0) {
        return 21;
    }
    if (strcmp(tempSignal, "SIGTTOU") == 0) {
        return 22;
    }
    counter++;
    return -1;
}*/

const char* signalReturnVal(int tempSignal) {//CONVERTING SIGNALS TO STRINGS
    if (tempSignal == 1) {
        return "SIGHUP";
    }
    if (tempSignal == 2) {
        return "SIGINT";
    }
    if (tempSignal == 3) {
        return "SIGQUIT";
    }
    if (tempSignal == 4) {
        return "SIGILL";
    }
    if (tempSignal == 5) {
        return "SIGTRAP";
    }
    if (tempSignal == 6) {
        return "SIGABRT";
    }
    if (tempSignal == 7) {
        return "SIGBUS";
    }
    if (tempSignal == 8) {
        return "SIGFPE";
    }
    if (tempSignal == 9) {
        return "SIGKILL";
    }
    if (tempSignal == 11) {
        return "SIGSEGV";
    }
    if (tempSignal == 13) {
        return "SIGPIPE";
    }
    if (tempSignal == 14) {
        return "SIGALRM";
    }
    if (tempSignal == 15) {
        return "SIGTERM";
    }
    if (tempSignal == 16) {
        return "SIGSTKFLT";
    }
    if (tempSignal == 17) {
        return "SIGCHLD";
    }
    if (tempSignal == 18) {
        return "SIGCONT";
    }
    if (tempSignal == 19) {
        return "SIGSTOP";
    }
    if (tempSignal == 30 || tempSignal == 10 || tempSignal == 16) {
        return "SIGUSR1";
    }
    if (tempSignal == 31 || tempSignal == 12 || tempSignal == 17) {
        return "SIGUSR2";
    }
    if (tempSignal == 20) {
        return "SIGCHLD";
    }
    if (tempSignal == 21) {
        return "SIGTTIN";
    }
    if (tempSignal == 22) {
        return "SIGTTOU";
    }
    if (tempSignal == 23) {
        return "SIGURG";
    }
    if (tempSignal == 24) {
        return "SIGXCPU";
    }
    if (tempSignal == 25) {
        return "SIGXFSZ";
    }
    if (tempSignal == 26) {
        return "SIGVTLALRM";
    }
    if (tempSignal == 27) {
        return "SIGPROF";
    }
    if (tempSignal == 28) {
        return "SIGWINCH";
    }
    if (tempSignal == 29) {
        return "SIGIO or SIGPOLL";
    } else {
        return "Unidentified Signal";
    }
}

void handler(int signo) {//NEW HANDLER
    time(&seconds);
    counter++;
    signal(signo, handler);
    if (signo == SIGTERM) {
        termcounter++;
        printf("%s received at %ld\n", signalReturnVal(signo), seconds);
    } else
        printf("%s received at %ld\n", signalReturnVal(signo), seconds);
}

int main(int argc, char** argv) {
    fprintf(stderr, "PID: %d\n", getpid());
    signal(SIGALRM, handler); //REDIRECT EACH EACH ALARM
    signal(SIGBUS, handler);
    signal(SIGCHLD, handler);
    signal(SIGCONT, handler);
    signal(SIGEMT, handler);
    signal(SIGFPE, handler);
    signal(SIGHUP, handler);
    signal(SIGILL, handler);
    signal(SIGINFO, handler);
    signal(SIGINT, handler);
    signal(SIGIO, handler);
    signal(SIGKILL, handler);
    signal(SIGPIPE, handler);
    //signal(SIGPROF handler);
    //signal(SIGQUIT handler);
    signal(SIGSEGV, handler);
    signal(SIGSTOP, handler);
    signal(SIGTSTP, handler);
    signal(SIGSYS, handler);
    signal(SIGTERM, handler);
    signal(SIGTRAP, handler);
    signal(SIGTTIN, handler);
    signal(SIGTTOU, handler);
    signal(SIGWINCH, handler);
    signal(SIGURG, handler);
    signal(SIGVTALRM, handler);
    signal(SIGXCPU, handler);
    //signal(SIGXFSZ handler);
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    signal(SIGTERM, handler);
    signal(SIGTTOU, handler);
    while (termcounter != 3) {
        pause();
    }
    /*if (signal(SIGUSR1, sig_usr) == SIG_ERR)
        printf("can't catch SIGUSR1");
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
        printf("can't catch SIGUSR2");
    for ( ; ; )
        pause();*/

    fprintf(stderr, "Signal Counter: %d", counter);

    return (EXIT_SUCCESS);
}

