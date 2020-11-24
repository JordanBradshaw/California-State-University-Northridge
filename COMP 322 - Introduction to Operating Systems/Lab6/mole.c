#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char** argv) {
    char molePath[1024];
    char path[1000];
    strcpy(path, argv[2]);//ARGV[1] = 1 then mole 1 // ARGV[2] PATH TO LOG FILE && MOLE PROGRAM
    snprintf(molePath, 1023, "%s/lab6.log", path);///WAS BUSY WITH FINALS BUT GOT TIME TO DIAGNOSE EVERYTHING
    FILE* fp=fopen(molePath, "a"); ///////WHEN DAEMON CHDIR EVEN IF CALLING THE PATH STILL WANTS TO PLACE lab6.log IN ROOT
    if (fp==NULL) {///^-------------------DUE TO THIS. SO NOW WERE GOIN TO PASS PATH AS SECOND ARGUMENT
        fprintf(stderr, "Lab creation failed");
    }
    if (fp!=0) {
        char* mole;
        if (argc>1&&strcmp(argv[1], "1")==0)
            mole="Pop mole1\n";
        else
            mole="Pop mole2\n";
        fputs(mole, fp);
    }
    fclose(fp);
    return 0;
}

