/* NAME: Javier Andres Tarazona Jimenez, Nahian Sajid 
   NSID: elr490, Zas742
   Student Number: 11411898, 11309563

   CMPT 332 Term 1 2024

   Assignment 1
*/

#include "list.h"
#include <stdio.h>

/*ListRemove SKELETON*/
void *ListRemove(LIST *list) {
    if (list == NULL) {
        printf("Error in procedure ListRemove: invalid parameter\n");
        return NULL;
    }
    printf("Got to procedure ListRemove\n");
    return NULL;  /*return PLACEHOLDER*/
}

/*ListFree SKELETON*/
void ListFree(LIST *list, void (*itemFree)(void *)) {
    if (list == NULL || itemFree == NULL) {
        printf("Error in procedure ListFree: invalid parameter\n");
        return;
    }
    printf("Got to procedure ListFree\n");
}
