/*
NAMEs: Javier Andres Tarazona Jimenez, Steven Baldwin
NSIDs: elr490, sjb956
Student Numbers: 11411898, 11300210
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#include <defs.h>

/*Usage Steps:
 * 1. Calculate Normalization Constant
 * 2. Find Zipf random number*/

/* Get the denominator, normalization constant
 * by providing the range N and the Zipf exponent s*/
double normalization_constant(int N, double s){
    int i;
    double denom;

    denom = 0.0;

    for (i=1; i<=N; i++){
        denom += 1.0 / pow(i, s);
    }

    return denom;
}

/*Get the zipf number by providing the range N,
 * teh zipf exponent s and the normalization constant
 * ( normalization_constant )*/
unsigned int zipf_random_number(int N, double s, double C){
    int number;
    double ran, sum;

    ran = (double)rand() / RAND_MAX; /*Random Num between 0 to 1*/
    sum = 0.0; /*Sum used to know when r was reached*/

    for (number = 1; number <= N; number++){
        sum += ( 1 / pow(number, s) ) / C;
        if ( ran < sum ){ /*Ran number was reached*/
            return number-1 ; /*As we want value 0, then minus 1*/
        }
    }

    /*If the sum was not reached, take the number that had,
     * and as we want 0, minus 1*/
    return number-1 ;
}

/* Get the denominator, normalization constant
 * for ZIPF virtual address */
double get_virtual_normalization_constant(){
    return normalization_constant(NUM_VIRTUAL_PAGES, ZIPF_EXPO);
}

/* Get a virtual zipf address. Provide
 * virtual normalization constant
 * calling get_virtual_normalization_constant */
unsigned int zipf_virtual_address(double C){
    unsigned int page_start;

    page_start = zipf_random_number(
            NUM_VIRTUAL_PAGES, ZIPF_EXPO, C);
    page_start = page_start * PAGESIZE;

    return page_start;
}