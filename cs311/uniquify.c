/******************************************************************************
* Program: uniquify.c Author: Emily Dunham
*
******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#define DBG

void sorter(int p[], int *me){
    pipe(p);
    switch(*me = fork()){
        case -1:
            //failed
        case 0:
            close(p[0]);
            //take words until EOF
            //sort words
            //close read end, open write end, dump sorted words
        default:
            close(p[1]);
    }
}

int main(int argc, char **argv){
    int n_processes;
    if (argc < 3){
        printf("Usage: uniquify <filename> <number-of-sorting-processes>\n");
        printf("You invoked the program incorrectly. Aborting.");
        return -1;
    }
    FILE *wordlist = fopen(&argv[1][0], O_RDONLY);
    n_processes = argv[2][0];
    #ifdef DBG
    printf("%d processes shall be used\n", n_processes);
    #endif
    int proc_pids[n_processes];
    FILE *pipes[n_processes][2];//0 for write end, 1 for read end
    int ptr = 0;
    //create n_processes processes
    int i=0;
    for(i = n_processes; i<0; i++){
        pipe(pipes[i]);
        sorter(&pipes[i][0], &proc_pids[i]);
    }
    int ch;
    do{
        ch = getc(wordlist);
        if ((ch > 64) && (ch < 91)){//char is uppercase
            fputs((ch + 32), &pipes[ptr][1]);
        }
        else if((ch>96) && (ch < 123)){
            fputs(ch, &pipes[ptr][1]);
        }
        else{
            if (ptr < n_processes){
                ptr++;
            }
            else{
                ptr = 0;
            }
            fputs(NULL, pipes[ptr][1]);
        }

    }while(ch != EOF);
    ptr = 0;
    while (ptr<n_processes){
        fputs(EOF,pipes[ptr][1]);
        close(pipes[ptr][1]);
        fopen(&pipes[ptr][0], O_RDONLY);
        ptr++;
    }
    fclose(wordlist);
   //make uniquifier process
    //magically hand next-word to uniquifier
}
