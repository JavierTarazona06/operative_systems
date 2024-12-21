/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin 
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 1
*/

#include <stdio.h>
#include <list.h>


/* Creates a new empty list, returns a reference pointer on success,
 * returns a NULL pointer on failure 
 */
LIST *ListCreate() /*done*/
{
  /*
  static int libraryHasBeenInitialized = 0;
  if (libraryHasBeenInitialized == 0) {
    libraryHasBeenInitialized = 1;

  }
  */
  extern int numberActiveLists;
  extern LIST listMem[];
  LIST createdList = {0, 0, NULL, NULL, NULL};


  if (numberActiveLists == MAX_LISTS) {
    return NULL;
  }

  listMem[numberActiveLists] = createdList; 
  numberActiveLists++;


  return &listMem[numberActiveLists-1];
}

/* Add new item to list directly after current item.
 * Current item becomes new item. If curr pointer at list tail,
 * item added at the end. Return 0 on success, -1 on failure.
 */
int ListAdd(LIST *list, void *item) /*done*/
{
  extern int numberActiveNodes;
  extern NODE nodeMem[];
  NODE createdNode = {NULL, NULL, NULL};



  if (item == NULL) {
    printf("Error in procedure ListAdd: invalid parameter\n");
    return -1;
  }
  if (numberActiveNodes == MAX_NODES) {
    return -1;
  }


  /*add to memory*/
  createdNode.item = item;
  createdNode.next = NULL;
  createdNode.prev = NULL;
  nodeMem[numberActiveNodes] = createdNode;
  

  

  if (list->numberItems == 0) {
    list->first = &nodeMem[numberActiveNodes];
    list->last = &nodeMem[numberActiveNodes];
    list->curr = &nodeMem[numberActiveNodes];
    list->numberItems++;
  }
  else {
    if (list->curr->next == NULL) { /*IF CURSOR LAST*/
      nodeMem[numberActiveNodes].prev = list->curr;
      list->curr->next = &nodeMem[numberActiveNodes];

      list->last = &nodeMem[numberActiveNodes];
      list->curr = &nodeMem[numberActiveNodes];
    }
    else {                              /*CAN NEVER ADD TO FIRST WITH LISTADD()*/
      nodeMem[numberActiveNodes].next = list->curr->next;
      nodeMem[numberActiveNodes].prev = list->curr;
      
      
      list->curr->next->prev = &nodeMem[numberActiveNodes];
      list->curr->next = &nodeMem[numberActiveNodes];

      
      list->curr = &nodeMem[numberActiveNodes];
    }
    /*IF NOT ADDING TO ZERO ALWAYS DO THIS*/
    list->cursorOffset++;
    list->numberItems++;
  }

  numberActiveNodes++;
  return 0;
}
/* Add item to list directly before current item.
 * Current item becomes new item. If curr pointer at list head,
 * item added at the start. Return 0 on success, -1 on failure.
 */
int ListInsert(LIST *list, void *item) /*done*/
{
  extern int numberActiveNodes;
  extern NODE nodeMem[];
  NODE createdNode = {NULL, NULL, NULL};

  if (item == NULL) {
    printf("Error in procedure ListInsert: invalid parameter\n");
    return -1;
  }
  if (numberActiveNodes == MAX_NODES) {
    return -1;
  }
  /*add to memory*/
  createdNode.item = item;
  createdNode.next = NULL;
  createdNode.prev = NULL;
  nodeMem[numberActiveNodes] = createdNode;
  
  if (list->numberItems == 0) {
    list->first = &nodeMem[numberActiveNodes];
    list->last = &nodeMem[numberActiveNodes];
    list->curr = &nodeMem[numberActiveNodes];
    list->numberItems++;
  }
  else {
    if (list->curr->prev == NULL) { /*IF CURSOR FIRST*/
      nodeMem[numberActiveNodes].next = list->curr;
      list->curr->prev = &nodeMem[numberActiveNodes];

      list->first = &nodeMem[numberActiveNodes];
      list->curr = &nodeMem[numberActiveNodes];
    }
    else {
      nodeMem[numberActiveNodes].prev = list->curr->prev;
      nodeMem[numberActiveNodes].next = list->curr;
      
      list->curr->prev->next = &nodeMem[numberActiveNodes];
      list->curr->prev = &nodeMem[numberActiveNodes];

      list->curr = &nodeMem[numberActiveNodes];
    }
    list->numberItems++;
  }

  numberActiveNodes++;
  return 0;
}

/* Add item to the end of the list. Current item becomes new item.
 * Return 0 on success, -1 on failure.
 */
int ListAppend(LIST *list, void *item) /*done*/
{
  extern int numberActiveNodes;
  extern NODE nodeMem[];
  NODE createdNode = {NULL, NULL, NULL};

  if (item == NULL) {
    printf("Error in procedure ListAppend: invalid parameter\n");
    return -1;
  }
  if (numberActiveNodes == MAX_NODES) {
    return -1;
  }

  /*add to memory*/
  createdNode.item = item;
  createdNode.next = NULL;
  createdNode.prev = NULL;
  nodeMem[numberActiveNodes] = createdNode;

  if (list->numberItems == 0) {
    list->first = &nodeMem[numberActiveNodes];
    list->last = &nodeMem[numberActiveNodes];
    list->curr = &nodeMem[numberActiveNodes];
    list->numberItems++;
  }
  else {
    nodeMem[numberActiveNodes].prev = list->last;
    list->last->next = &nodeMem[numberActiveNodes];

    list->last = &nodeMem[numberActiveNodes];
    list->curr = &nodeMem[numberActiveNodes];
  }

  list->numberItems++;
  list->cursorOffset = (list->numberItems)-1;
  numberActiveNodes++;
  return 0;
}

/* Add item to the front of the list. Current item becomes new item.
 * Return 0 on success, -1 on failure.
 */
int ListPrepend(LIST *list, void *item) /*done*/
{
  extern int numberActiveNodes;
  extern NODE nodeMem[];
  NODE createdNode = {NULL, NULL, NULL};

  if (item == NULL) {
    printf("Error in procedure ListPrepend: invalid parameter\n");
    return -1;
  }
  if (numberActiveNodes == MAX_NODES) {
    return -1;
  }
  /*add to memory*/
  createdNode.item = item;
  createdNode.next = NULL;
  createdNode.prev = NULL;
  nodeMem[numberActiveNodes] = createdNode;

  if (list->numberItems == 0) {
    list->first = &nodeMem[numberActiveNodes];
    list->last = &nodeMem[numberActiveNodes];
    list->curr = &nodeMem[numberActiveNodes];
    list->numberItems++;
  }
  else {
    nodeMem[numberActiveNodes].next = list->first;
    list->first->prev = &nodeMem[numberActiveNodes];

    list->first = &nodeMem[numberActiveNodes];
    list->curr = &nodeMem[numberActiveNodes];
  }

  list->numberItems++;
  list->cursorOffset = 0;
  numberActiveNodes++;
  return 0;
}

/* Add list2 to the end of list1. Current item becomes curr pointer item
 * of list1. list2 does not exist after this function is called.\
 */
void ListConcat(LIST *list1, LIST *list2) {
  /*if (list1 == NULL || list2 == NULL) {
    printf("Error in procedure ListConcat: invalid parameter\n");
    return -1;
  }*/

  printf("Got to procedure ListConcat\n");
  return;
}