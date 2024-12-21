/* NAME: Javier Andres Tarazona Jimenez, Nahian Sajid 
   NSID: elr490, Zas742
   Student Number: 11411898, 11309563

   CMPT 332 Term 1 2024

   Assignment 1
*/



#include "list.h"
#include <stdio.h>

/* ListFirst skeleton*/
void *ListFirst(LIST *list) {
    if (list == NULL) {
        printf("Error in procedure ListFirst: invalid parameter\n");
        return NULL;
    }
    printf("Got to procedure ListFirst\n");
    return NULL;  /* return PLACEHOLDER*/
}

/* ListLast skeleton*/
void *ListLast(LIST *list) {
    if (list == NULL) {
        printf("Error in procedure ListLast: invalid parameter\n");
        return NULL;
    }
    printf("Got to procedure ListLast\n");
    return NULL;  /* return PLACEHOLDER*/
}

/* ListNext skeleton*/
void *ListNext(LIST *list) {
    if (list == NULL) {
        printf("Error in procedure ListNext: invalid parameter\n");
        return NULL;
    }
    printf("Got to procedure ListNext\n");
    return NULL;  /* return PLACEHOLDER*/
}

/* ListPrev skeleton*/
void *ListPrev(LIST *list) {
    if (list == NULL) {
        printf("Error in procedure ListPrev: invalid parameter\n");
        return NULL;
    }
    printf("Got to procedure ListPrev\n");
    return NULL;  /*  return PLACEHOLDER*/
}

