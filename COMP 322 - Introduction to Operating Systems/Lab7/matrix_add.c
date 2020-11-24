#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <aio.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
struct aiocb cbNext;
struct aiocb cbPrev;
struct aiocb cbCurr;
int CURRENT, last, next;
int retCurrRead, retCurrWrite, retPrevWrite, retNext, retNextRead, retNextWrite;
#define TOTAL ((size*size*4)+size) //(THIS IS DUE TO NEW LINE SO 8x8 matrix 4 bits each and 8 newline bits))
#define BLOCKSIZE blockSize //WANTED COLOR CLARITY  //       & size amount of new lines
#define ROW (size*4)+1 ////8 INT 4 CHARS + 1 FOR NEW LINE
#define NEXT CURRENT
#define PREV CURRENT-blockSize
#define CURROW curRow
#define CURINT curInt
size_t blockSize=0;
int scalar;
int size;
int blocks;

void loadIn(struct aiocb* temp, off_t off) {
    memset(temp, 0, sizeof(struct aiocb));
    temp->aio_fildes=fileno(stdin);
    temp->aio_nbytes=blockSize;
    temp->aio_offset=off;
    temp->aio_buf=malloc(blockSize);
    temp->aio_reqprio=0;
}
void loadOut(struct aiocb* temp, off_t off) {
    temp->aio_fildes=fileno(stdout);
    temp->aio_nbytes=blockSize;
    temp->aio_offset=off;
}
void matrixAdd(struct aiocb* temp) {
    char newLineBuff[ROW+1];
    int curRow=0;
    int curInt=0;
    char charNum[5]; //4 DIGIT AND /0
    int intNum; /////// THE -1 IS TO COMPENSATE FOR \N ADDITION AT START
    for (CURROW=0; CURROW<BLOCKSIZE; CURROW+=ROW) {///BREAKS DOWN EACH ROW
        for (CURINT=CURROW; CURINT<(ROW+CURROW); CURINT+=4) {//BREAKS DOWN EACH INT
            memset(charNum, NULL, 5); //EXMPY OUT
            memcpy(charNum, temp->aio_buf+(CURINT), 4); //GRAB 4 CHARS OF BUFFER
            intNum=atoi(charNum); //INT VAL OF STRING
            intNum+=scalar; //ADD SCALAR
            memset(charNum, NULL, 5); //CLEAR OLF VAL
            sprintf(charNum, "%4d", intNum); //MAKE IT TAKE 4 CHARS REGARDLESS
            memcpy(temp->aio_buf+CURINT, charNum, 4); //PUT BACK IN CBCURR->BUFFER
        }
        memset(newLineBuff, '\0', ROW+1); //EMPTY OUT
        snprintf(newLineBuff, ROW, "%s", temp->aio_buf+CURROW); //GRAB ROW OFFSET BY CURROW STORE IN NEWLINEBUFF
        newLineBuff[ROW-1]='\n'; ////THROW NEW LINE AT END
        memcpy(temp->aio_buf+(CURROW+ROW), newLineBuff, sizeof(ROW)); //COPY NEWLINE INTO BUFFER
        memcpy(temp->aio_buf+CURROW, newLineBuff, ROW); //PUT BACK IN CBCURR->BUFFER
    }
}
void matrixCalc() {//the lack of organization was irritating
    int CURRENT=0;
    blockSize=(TOTAL/blocks); //THIS IS TO COMPINSATE FOR NEW LINE COUNTING AS OFFSET
    fprintf(stderr, "TotalSize: %d\n", TOTAL);
    fprintf(stderr, "BlockSize: %ld\n", blockSize);
    //////////////////////////////////////ORIGINAL LOAD (KEEP)
    loadIn(&cbCurr, 0);
    retCurrRead=aio_read(&cbCurr);
    if (retCurrRead<0) {
        fprintf(stderr, "AIO CURR READ FAIL (1)");
    }
    while (aio_error(&cbCurr)==EINPROGRESS) {
    }
    aio_return(&cbCurr);
    ////////////////////////////////////// END OF PRE LOOP
    for (CURRENT=BLOCKSIZE; CURRENT<TOTAL; CURRENT+=BLOCKSIZE) {
        /////////////////////////////////////NEXT LOAD (IN LOOP))
        //fprintf(stderr, "Current Block %ld\n", (CURRENT - BLOCKSIZE));
        loadIn(&cbNext, NEXT);
        retNextRead=aio_read(&cbNext);
        //fprintf(stderr,"%s", cbNext.aio_buf);
        if (retNextRead<0) {
            fprintf(stderr, "AIO READ NEXT FAIL (2)");
        }
        while (aio_error(&cbNext)==EINPROGRESS) {
        }
        aio_return(&cbNext);
        ///////////////////////////////////////// MATRIX ADD
        matrixAdd(&cbCurr);
        ////////////////////////////////////////  WRITE PREV
        memcpy(&cbPrev, &cbCurr, sizeof(struct aiocb));
        loadOut(&cbPrev, PREV);
        //fprintf(stderr, "%s", cbCurr.aio_buf);
        retPrevWrite=aio_write(&cbPrev);
        if (retPrevWrite<0) {
            fprintf(stderr, "\nAIO PREV WRITE FAIL (3)\n");
        }
        while (aio_error(&cbPrev)==EINPROGRESS) {
        }
        if ((retPrevWrite=aio_return(&cbPrev))>0) {
            //fprintf(stderr, "Success\n");
        }
        else {
            int errnum;
            fprintf(stderr, "Fail %d <~~\n", errno);
            perror("PRINT ERROR");
        }/////////////////////////// SYNC OUT MOVE NEXT TO CURR
        /*if (aio_fsync(O_SYNC, &cbPrev) != -1) {
            fprintf(stderr, "\nSync success\n");
        }*/
        memcpy(&cbCurr, &cbNext, sizeof(struct aiocb));
    }////////////////////////////////////////////END OF FOR LOOP
    /////////////////////////////////////////////////
    /////////////////////////////////////////////CURRENT FINAL WRITE
    matrixAdd(&cbCurr);
    loadOut(&cbCurr, (PREV));
    cbCurr.aio_nbytes=(blockSize-1); //TO COUNT FOR LAST LINE NOT HAVING /N
    retCurrWrite=aio_write(&cbCurr);
    if (retCurrWrite<0) {
        fprintf(stderr, "AIO CURR WRITE FAIL (4)");
    }
    while (aio_error(&cbCurr)==EINPROGRESS) {
    }
    retCurrWrite=aio_return(&cbCurr);
    /////////////////////////////END OF MATRIX CALC
}
int main(int argc, char** argv) {
    //VALID ARGS FOR COMPILER TO NOT FLAG
    if (argc!=3) {
        fprintf(stderr, "Arguments should be Size Blocks < matrix1.txt > matrix2.txt");
        return (EXIT_FAILURE);
    }
    clock_t begin=clock(); //TIMER START
    size=atoi(argv[1]), blocks=atoi(argv[2]);
    if (size%blocks) {
        fprintf(stderr, "Size / Blocks doesn't divide evenly");
    }
    scalar=rand()%101;
    fprintf(stderr, "Scalar: %d\n", scalar);
    matrixCalc(size, blocks);
    clock_t end=clock();
    double totalTime=(double)(end-begin)/CLOCKS_PER_SEC;
    fprintf(stderr, "Total Seconds Elapsed: %lf\n", totalTime);
    return (EXIT_SUCCESS);
}

