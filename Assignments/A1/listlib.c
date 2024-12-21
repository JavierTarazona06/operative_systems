/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin 
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 1
   
   Allocating memory and defining max lists and nodes for List Library.
   This will be a doubly linked list.
*/

#include <stdio.h>
#include <list.h>

/* Statically allocate memory for lists and nodes at compile time */
LIST listMem[MAX_LISTS];
NODE nodeMem[MAX_NODES];
int numberActiveLists = 0;
int numberActiveNodes = 0;

/* A list may have between 0 and MAX_NODES nodes, but all lists together
 * may not have more than MAX_NODES at any point in time. */
/* A Node has 3 pointers, a List has 3 pointers */


