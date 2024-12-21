/* NAME: Javier Andres Tarazona Jimenez, Nahian Sajid 
   NSID: elr490, Zas742
   Student Number: 11411898, 11309563

   CMPT 332 Term 1 2024

   Assignment 1
*/


#include "list.h"
#include <stdio.h>

int main() {
    // make a new list
    LIST *list = ListCreate();
    if (list == NULL) {
        printf("ListCreate returned NULL\n");
    }

    // Test first one ListAdd
    int item1 = 10;
    if (ListAdd(list, &item1) == 0) {
        printf("ListAdd succeeded\n");
    }

    // Test second ListFirst
    void *firstItem = ListFirst(list);
    if (firstItem == NULL) {
        printf("ListFirst returned NULL\n");
    }

    // Test third ListLast
    void *lastItem = ListLast(list);
    if (lastItem == NULL) {
        printf("ListLast returned NULL\n");
    }

    // Test fourth ListNext
    void *nextItem = ListNext(list);
    if (nextItem == NULL) {
        printf("ListNext returned NULL\n");
    }

    // Test fifth ListPrev
    void *prevItem = ListPrev(list);
    if (prevItem == NULL) {
        printf("ListPrev returned NULL\n");
    }

    // Test sixth ListRemove
    void *removedItem = ListRemove(list);
    if (removedItem == NULL) {
        printf("ListRemove returned NULL\n");
    }

    // Test seaveth ListFree
    ListFree(list, NULL);  // NULL PLACEHOLDER
    printf("ListFree called\n");

    return 0;
}
