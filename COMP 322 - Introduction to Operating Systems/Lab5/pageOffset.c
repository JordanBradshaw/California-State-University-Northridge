/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: yups
 *
 * Created on April 30, 2020, 3:40 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
unsigned int offset(unsigned int address,int size){
    unsigned offset = (address % size);
    return offset;
}
unsigned int pageNum(unsigned int address,int size){
    unsigned int pageNum = (address / size);
    return pageNum;
}



int main(int argc, char** argv) {
    int size = 4096;
    unsigned int address = 0;
    if (argc == 2) {
        address = atoi(argv[1]);
        fprintf(stdout, "The address %d contains\n",address);
        fprintf(stdout, "The page number is %d\n",pageNum(address,size));
        fprintf(stdout, "Offset is %d", offset(address,size));
        exit(EXIT_SUCCESS);
    } else {
        fprintf(stdout, "Need only 1 argument.");
    }
    return (EXIT_FAILURE);
}

