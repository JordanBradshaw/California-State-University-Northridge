#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define bool int

int ConvertDIgn(char* n) { //Convert from binary to decimal
    char temp[9];
    memcpy(temp, n, sizeof temp);
    temp[0]='0';
    int convertD=0, i=0, remainder;
    int numberConv=atoi(temp);
    while (numberConv!=0) {
        remainder=numberConv%10;
        numberConv/=10;
        convertD+=remainder*pow(2, i);
        ++i;
    }
    return convertD;
}
int ConvertD(char* n) { //Convert from binary to decimal
    int convertD=0, i=0, remainder;
    int numberConv=atoi(n);
    while (numberConv!=0) {
        remainder=numberConv%10;
        numberConv/=10;
        convertD+=remainder*pow(2, i);
        ++i;
    }
    return convertD;
}
bool getParity(int n) {
    bool parity=0;
    while (n) {
        parity=!parity;
        n=n&(n-1);
    }
    return parity;
}
int contains01(char* n) {
    int counter=0;
    char temp[9];
    memcpy(temp, n, sizeof temp);
    for (int i=0; i<8; i++) {
        if (temp[i]=='0'||temp[i]=='1') {
        }
        else {
            counter++;
        }
    }
    return counter;
}
void getASCII(int n) {
    char* keys[50][6];
    keys[0][0]="NUL";
    keys[1][0]="SOH";
    keys[2][0]="STX";
    keys[3][0]="ETX";
    keys[4][0]="EOT";
    keys[5][0]="ENQ";
    keys[6][0]="ACK";
    keys[7][0]="BEL";
    keys[8][0]="BS";
    keys[9][0]="TAB";
    keys[10][0]="LF";
    keys[11][0]="VT";
    keys[12][0]="FF";
    keys[13][0]="CR";
    keys[14][0]="SO";
    keys[15][0]="SI";
    keys[16][0]="DLE";
    keys[17][0]="DC1";
    keys[18][0]="DC2";
    keys[19][0]="DC3";
    keys[20][0]="DC4";
    keys[21][0]="NAK";
    keys[22][0]="SYN";
    keys[23][0]="ETB";
    keys[24][0]="CAN";
    keys[25][0]="EM";
    keys[26][0]="SUB";
    keys[27][0]="ESC";
    keys[28][0]="FS";
    keys[29][0]="GS";
    keys[30][0]="RS";
    keys[31][0]="US";
    keys[32][0]="SPACE";
    keys[33][0]="DEL";
    if (n<=32) {
        printf("% 8s", keys[n][0]);
    }
    else if (n>=33&&n<=126) {
        printf("% 8c", n);
    }
    else if (n==127) {
        printf("% 8s", keys[33][0]);
    }
}
void DecodeText(char* number) {
    if (contains01(number)!=0) {
        system("clear");
        printf("The data contained a char that was not 0 or 1");
        exit(0);
    }
    int decimal;
    printf("% 8s", number);
    printf("% 8d", ConvertDIgn(number));
    decimal=ConvertDIgn(number);
    getASCII(decimal);
    printf("% 8s", getParity(ConvertD(number))?"odd":"even");
    printf("\n");
}
int main(int argc, char** argv) {
    char number[20];
    char tempL[10000];
    char* line=NULL;
    size_t len=0;
    ssize_t read;
    char* token;
    const char sp[2]=" ";
    printf("BINARY   DECIMAL   ASCII  PARITY\n");
    if (argc==2&&strcmp(argv[1], ("-"))!=0) {
        FILE* fileL=fopen(argv[1], "r"); //read
        if (fileL==NULL) { //if file fails run this
            printf("Could not find file\n");
            exit(-1);
        }
        read=getline(&line, &len, fileL);
        token=strtok(line, sp);
        while (token!=NULL) {
            char buffer[9];
            snprintf(buffer, 9, "%s", token);
            int digits=strlen(buffer);
            for (int i=digits; i<8; i++) {
                buffer[i]='0';
            }
            DecodeText(buffer);
            token=strtok(NULL, sp);
        }
    }
    else if (strcmp(argv[1], ("-"))==0) {
        for (int i=2; i<argc; i++) {
            char buffer[9];
            int digits;
            snprintf(buffer, 9, "%s", argv[i]);
            digits=strlen(buffer);
            for (int i=digits; i<8; i++) {
                buffer[i]='0';
            }
            DecodeText(buffer);
        }
    }
    else {
        for (int i=1; i<argc; i++) {
            char buffer[9];
            int digits;
            snprintf(buffer, 9, "%s", argv[i]);
            digits=strlen(buffer);
            for (int i=digits; i<8; i++) {
                buffer[i]='0';
            }
            DecodeText(buffer);
        }
    }
    return (EXIT_SUCCESS);
}