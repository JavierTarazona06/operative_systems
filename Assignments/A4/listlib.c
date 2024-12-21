/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin 
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 1
   
   Allocating memory and defining max lists and nodes for List Library.
   This file handles all the memory management in the library.
*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* Statically allocate memory for lists and nodes at compile time */
/* A list may have between 0 and MAX_NODES nodes, but all lists together
 * may not have more than MAX_NODES at any point in time. */
/* A Node has 3 pointers, a List has 3 pointers */

int nodeMemMultiplier = 1;
int listMemMultiplier = 1;



struct LIST *listMem;
struct NODE *nodeMem;

struct NODE *freeLISTList;
struct NODE *freeNODEList;

NODE *pfreeLISTList;
NODE *pfreeNODEList;

int numberActiveLists = 0;
int numberActiveNodes = 0;


void InitFreeLISTList(int startIndex, int endIndex);
void InitFreeNODEList(int startIndex, int endIndex);

/* This function is called once at the beginning of the program
to initalize the memory blocks we'll be using for lists, nodes,
the (lists free list) and the (nodes free list).*/
void InitFreeLists() {
   /*actual memory*/
   listMem = malloc(MAX_LISTS * sizeof(struct LIST));
   nodeMem = malloc(MAX_NODES * sizeof(struct NODE));

   /*free lists*/
   freeLISTList = malloc(MAX_LISTS * sizeof(struct NODE));
   freeNODEList = malloc(MAX_NODES * sizeof(struct NODE));

   /*pointers to free lists*/
   pfreeLISTList = &freeLISTList[0];
   pfreeNODEList = &freeNODEList[0];

   /*have free lists actually point to free memory*/
   InitFreeLISTList(0, MAX_LISTS-1);
   InitFreeNODEList(0, MAX_NODES-1);
}

/* This function initializes the list free list pointers
each to a free block of memory in the list memory block.*/
void InitFreeLISTList(int startIndex, int endIndex) {
   int index;
   
   for (index = startIndex; index <= endIndex; index++) {
      freeLISTList[index].item = &listMem[index];
   }
   return;
}

/* This function initializes the node free list pointers
each to a free node from the node memory block*/
void InitFreeNODEList(int startIndex, int endIndex) {
   int index;

   for (index = startIndex; index <= endIndex; index++) {
      freeNODEList[index].item = &nodeMem[index];
   }
   return;
}

/*
(LIST ALLOCATOR)
Returns a memory block that holds a new empty list\
*/
LIST *GetListMem() {
   LIST *pListToReturn;
   NODE pointingNode;
   

   if (numberActiveLists == MAX_LISTS) {
      return NULL;
   }
   
   
   pointingNode = freeLISTList[numberActiveLists];
   pListToReturn = pointingNode.item;

   /*initialize list values*/
   pListToReturn->numberItems = 0;
   pListToReturn->first = NULL;
   pListToReturn->curr = NULL;
   pListToReturn->last = NULL;


   numberActiveLists++;
   return pListToReturn;
}

/*
(NODE ALLOCATOR)
Returns a memory block that holds a new empty node
 */
NODE *GetNodeMem() {
   NODE *pNodeToReturn;
   NODE pointingNode;
   
   if (numberActiveNodes == MAX_NODES) {
      return NULL;
   }
   
   
   pointingNode = freeNODEList[numberActiveNodes];
   pNodeToReturn = pointingNode.item;

   /*initialize node values*/
   pNodeToReturn->item = NULL;
   pNodeToReturn->next = NULL;
   pNodeToReturn->prev = NULL;

   numberActiveNodes++;
   return pNodeToReturn;
}


/*
(LIST DE-ALLOCATOR)
Adds a new pointer to the list free list, pointing to
the memory that once held the inputted list (listToFree).
 */
void FreeListMem(LIST *listToFree) {
   NODE newFreeNode;
   numberActiveLists--;

   
   /*new address is free*/
   newFreeNode.next = pfreeLISTList;
   newFreeNode.item = listToFree;
   /*store free address value at top of list*/
   freeLISTList[numberActiveLists] = newFreeNode;
   /*update pointer to free list*/
   pfreeLISTList = &freeLISTList[numberActiveLists];
   
   /*clear old data*/
   listToFree->numberItems = 0;
   listToFree->first = NULL;
   listToFree->curr = NULL;
   listToFree->last = NULL;
   return;
}



/*
(NODE DE-ALLOCATOR)
Adds a new pointer to the node free list, pointing to
the memory that once held the inputted node (nodeToFree).
 */
void FreeNodeMem(NODE *nodeToFree) {
   NODE newFreeNode;
   numberActiveNodes--;


   /*new address is free*/
   newFreeNode.next = pfreeNODEList;
   newFreeNode.item = nodeToFree;
   /*store free address value at top of list*/
   freeNODEList[numberActiveNodes] = newFreeNode;
   /*update pointer to free list*/
   pfreeNODEList = &freeNODEList[numberActiveNodes];
   
   /*clear old data*/
   nodeToFree->item = NULL;
   nodeToFree->next = NULL;
   nodeToFree->prev = NULL;
   return;
}

