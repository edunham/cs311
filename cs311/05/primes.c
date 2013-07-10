/******************************************************************************
* Program: primes.c     Author: Emily Dunham        Date: 11/20/2012
* 
* Credits: 
*   - Mathematical concept of how to make a block-wise sieve came from online
*     at http://create.stephan-brumme.com/eratosthenes/. This link also
*     supplied the idea of trying hard-coded divisibility checks to speed up
*     sieving.
*   - This link solved my segfault problems when creating the bitmap:
*   http://pleasemakeanote.blogspot.com/2008/06/2d-arrays-in-c-using-malloc.html 
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#define DBG
#define PRIME '1'
#define NOTPRIME '0'

int calc_block(int start, int length, char *mem){
    /* Assume memory is fully set to prime value*/
    #ifdef DBG
    printf("DBG: in calc_block, start is %d and length is %d\n", start, length);
    #endif
    int minJ;
    int primes = length;
    for (int i = 3; i*i <= (start + length); i++){
        if (i % 2 == 0)
            continue;
        if (i >= 3*3 && i % 3 == 0)
            continue;
        if (i >= 5*5 && i % 5 == 0)
            continue;
        if (i >= 7*7 && i % 7 == 0)
            continue;
        if (i >= 11*11 && i % 11 == 0)
            continue;
        if (i >= 13*13 && i % 13 == 0)
            continue;
        minJ = ((start+i-1)/i)*i;
        if (minJ < i*i)
            minJ = i*i;
        if ((minJ & 1) == 0)
            minJ += i;
        for (int j = minJ; j <= (start + length); j += 2*i){
            mem[(j - start)/2] = NOTPRIME;
            printf("\ti is %d, decrementing prime count\n", i);
            primes--;
        }
    }
    return primes;
}

int main(int argc, char **argv){
//----------------SETUP--------------------------------------------------------
    if(argc < 4){
        printf("primes.c by Emily Dunham. Usage:\n");
        printf("\tFirst argument is number up to which we shall find primes\n");
        printf("\tSecond argument is the number of threads or processes\n");
        printf("\tThird argument is t for threads or p for processes\n");
        return 0;
    }
    int max = atoi(argv[1]);
    int rows = atoi(argv[2]);
    int use_threads = 0;
    if (argv[3][0] == 't' || argv[3][0] == 'T'){
        use_threads = 1;
    }
    #ifdef DBG
    printf("DBG: max is %d and rows is %d and threads is %d\n", 
           max, rows, use_threads);
    #endif
//----------------MAKE BITMAP---------------------------------------------------
    //Yes, I know this isn't a proper bitmap. But if one put appropriate
    //headers and stuff, it could become a bitmap. However, considering the
    //fact that it's currently 8:30pm the night it's due, you may just have to
    //dock me some points and be content with a char[][]...
    int cols = max / rows;
    if (max % rows != 0)
        cols++;
    #ifdef DBG
    printf("DBG: cols is %d :) \n", cols);
    #endif
    char **data;
    data = malloc(rows * sizeof(char*));
    int i=0;
    int j=0;
    for(i; i < rows; i++){
        data[i] = (char*)malloc(cols * sizeof(char));
        for(j; j < cols; j++){
            data[i][j] = PRIME;
        }
        j=0;
    }
//---------------MAKE THREADS OR PROCESSES--------------------------------------
    //first serially to make sure it works
    int total_found = 0;
    int c = 0;
    for(c; c < rows; c++){
        #ifdef DBG
        printf("c is %d, calc_block gets %d %d\n", c,(c*cols),cols);
        #endif
        total_found += calc_block((c * cols), cols, data[c]);
    }

//--------------PRINT NUMBER OF PRIMES FOUND------------------------------------
    printf("found %i primes\n", total_found);

    return 0;
}
