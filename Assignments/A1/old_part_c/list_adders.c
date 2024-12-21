/* NAME: Javier Andres Tarazona Jimenez, Nahian Sajid 
   NSID: elr490, Zas742
   Student Number: 11411898, 11309563

   CMPT 332 Term 1 2024

   Assignment 1
*/

#include <stdio.h>
#include "list.h"

/*ListCreate skeleton*/

LIST *ListCreate() {
    printf("Got to procedure ListCreate\n");
    return NULL;  /*  return JUST A PLACEHOLDER*/
}

/* ListAdd skeleton*/
int ListAdd(LIST *list, void *item) {
    if (list == NULL || item == NULL) {
        printf("Error in procedure ListAdd: invalid parameter\n");
        return -1;
    }
    printf("Got to procedure  for ListAdd\n");
    return 0;  /*  return JUST A PLACEHOLDeR*/
}

/* ListAppend SKELETON */
int ListAppend(LIST *list, void *item) {
    if (list == NULL || item == NULL) {
        printf("Error in procedure ListAppend: invalid parameter\n");
        return -1;
    }
    printf("Got to procedure ListAppend\n");
    return 0;  /* return PLACEHOLDER*/
    }

/* ListPrepend SKELETON*/
int ListPrepend(LIST *list, void *item) {
    if (list == NULL || item == NULL) {
        printf("Error in procedure ListPrepend: invalid parameter\n");
        return -1;
    }
    printf("Got to procedure ListPrepend\n");
    return 0;  /*return PLACEHOLDER*/
}
