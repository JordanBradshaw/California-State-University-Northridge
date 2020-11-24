/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: yups
 *
 * Created on February 19, 2020, 6:39 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/times.h>
#include "unistd.h"
#include <time.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <time.h>

/*
 * 
 */

int convertByte2Bit(int tempByte) {//BIT SHIFT TO GET VALUE
    return ((tempByte >> 0) & 1);
}

void displayTimes(struct tms tempStart, struct tms tempEnd) {//CALULATE TIMES BUT END UP 0
    clock_t cpu_time = tempEnd.tms_cutime - tempStart.tms_cutime;
    clock_t utime = tempEnd.tms_utime - tempStart.tms_utime;
    clock_t stime = tempEnd.tms_stime - tempStart.tms_stime;
    clock_t cstime = tempEnd.tms_cstime - tempStart.tms_cstime;
    printf("USER: %jd SYS: %jd\n", (intmax_t) utime, (intmax_t) stime);
    printf("CUSER: %jd CSYS: %jd\n", (intmax_t) cpu_time, (intmax_t) cstime);
}

void calculateInfo(int tempPID) {
    int childStatus; //DECLARE VAFS
    pid_t wPID;
    if (tempPID > 0) { //IF PID IS > 0 THEN IN PARENT
        wait(&childStatus);
        //wPID = waitpid(tempPID, &childStatus, WUNTRACED);
        int exitStatus = WEXITSTATUS(childStatus); //RETREAVE VALUE FROM CHILD
        printf("PPID: %d, PID: %d CPID: %d, RETVAL: %d \n", getppid(), getpid(), tempPID, convertByte2Bit(exitStatus));
    } else { //PRINT STATEMENTS DEPENDING ON IF PARENT OR CHILD
        printf("PPID: %d, PID: %d\n", getppid(), getpid());
    }
}

int main(int argc, char** argv) {
    int pid = fork(); //FORK AND DECLARE VARS
    struct tms startTime; // STRUCT FOR CLOCK_T
    struct tms endTime;
    int childStatus = -1;
    pid_t wPID;
    time_t startSeconds, endSeconds;

    bool validPID = (pid >= 0) ? true : false;
    if (validPID == true) {
        if (pid == 0) {//PID RETURNS 0 IF IN CHILD
            calculateInfo(pid); //GET PID PPID ECT
            exit(0); //CLOSE WHEN FINISHED
        } else {//PID RETURNS PID OF CHILD (IN PARENT)
            startSeconds = time(NULL); //GET TIME IN SECONDS
            printf("START: %ld\n", startSeconds);
            times(&startTime);
            wPID = waitpid(pid, &childStatus, WUNTRACED); //WAIT FOR CHILD PROCESS TO STOP
            calculateInfo(pid);
            times(&endTime);
            displayTimes(startTime, endTime); //CALL DISPLAY USER / SYS
            endSeconds = time(NULL); //END TIME IN SECONDS
            printf("STOP: %ld\n", endSeconds);
        }
    } else {//VALID PID == FALSE SO!
        printf("Error Creating Child!");
    }


    return (EXIT_SUCCESS);
}

