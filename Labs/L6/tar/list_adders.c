/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin 
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 1
*/

#include <stdio.h>
#include "list.h"

extern void InitFreeLists();
extern LIST *GetListMem();
extern NODE *GetNodeMem();
extern void FreeListMem(LIST *listToFree);


/* Creates a new empty list, returns a reference pointer on success,
 * returns a NULL pointer on failure 
 */
LIST *ListCreate() 
{
  LIST *pNewList;

  /*First run initialization of free lists*/
  static int libraryHasBeenInitialized = 0;
  if (libraryHasBeenInitialized == 0) {
    libraryHasBeenInitialized = 1;
    printf("init free lists\n");
    InitFreeLists();
  }
  
  pNewList = GetListMem();
  if (pNewList == NULL) {
    return NULL;
  }
  return pNewList;
}

/* Add new item to list directly after current item.
 * Current item becomes new item. If curr pointer at list tail,
 * item added at the end. Return 0 on success, -1 on failure.
 */
int ListAdd(LIST *list, void *item) 
{
  NODE *pNewNode;

  if (list == NULL || item == NULL) {
    printf("Error in procedure ListAdd: invalid parameter\n");
    return -1;
  }
  
  pNewNode = GetNodeMem();
  if (pNewNode == NULL) {
    return -1;
  }
  pNewNode->item = item;
  
  if (list->numberItems == 0) {
    list->first = pNewNode;
    list->last = pNewNode;
    list->curr = pNewNode;
    list->numberItems++;
  }
  else {
    if (list->curr->next == NULL) { /*IF CURSOR LAST*/
      pNewNode->prev = list->curr;
      list->curr->next = pNewNode;

      list->last = pNewNode;
      list->curr = pNewNode;
    }
    else {                              /*CAN NEVER ADD TO FIRST WITH LISTADD()*/
      pNewNode->next = list->curr->next;
      pNewNode->prev = list->curr;
      
      
      list->curr->next->prev = pNewNode;
      list->curr->next = pNewNode;

      
      list->curr = pNewNode;
    }
    /*IF NOT ADDING TO ZERO ALWAYS DO THIS*/
    list->numberItems++;
  }

  return 0;
}
/* Add item to list directly before current item.
 * Current item becomes new item. If curr pointer at list head,
 * item added at the start. Return 0 on success, -1 on failure.
 */
int ListInsert(LIST *list, void *item) 
{
  NODE *pNewNode;

  if (list == NULL || item == NULL) {
    printf("Error in procedure ListInsert: invalid parameter\n");
    return -1;
  }
  pNewNode = GetNodeMem();
  if (pNewNode == NULL) {
    return -1;
  }
  pNewNode->item = item;

  
  
  if (list->numberItems == 0) {
    list->first = pNewNode;
    list->last = pNewNode;
    list->curr = pNewNode;
    list->numberItems++;
  }
  else {
    if (list->curr->prev == NULL) { /*IF CURSOR FIRST*/
      pNewNode->next = list->curr;
      list->curr->prev = pNewNode;

      list->first = pNewNode;
      list->curr = pNewNode;
    }
    else {
      pNewNode->prev = list->curr->prev;
      pNewNode->next = list->curr;
      
      list->curr->prev->next = pNewNode;
      list->curr->prev = pNewNode;

      list->curr = pNewNode;
    }
    list->numberItems++;
  }
  return 0;
}

/* Add item to the end of the list. Current item becomes new item.
 * Return 0 on success, -1 on failure.
 */
int ListAppend(LIST *list, void *item) 
{
  NODE *pNewNode;

  if (list == NULL || item == NULL) {
    printf("Error in procedure ListAppend: invalid parameter\n");
    return -1;
  }

  pNewNode = GetNodeMem();
  if (pNewNode == NULL) {
    return -1;
  }
  pNewNode->item = item;

  if (list->numberItems == 0) {
    list->first = pNewNode;
    list->last = pNewNode;
    list->curr = pNewNode;
    list->numberItems++;
  }
  else {
    pNewNode->prev = list->last;
    list->last->next = pNewNode;

    list->last = pNewNode;
    list->curr = pNewNode;
    list->numberItems++;
  }
  return 0;
}

/* Add item to the front of the list. Current item becomes new item.
 * Return 0 on success, -1 on failure.
 */
int ListPrepend(LIST *list, void *item) 
{
  NODE *pNewNode;

  if (list == NULL || item == NULL) {
    printf("Error in procedure ListPrepend: invalid parameter\n");
    return -1;
  }

  pNewNode = GetNodeMem();
  if (pNewNode == NULL) {
    return -1;
  }
  pNewNode->item = item;

  if (list->numberItems == 0) {
    list->first = pNewNode;
    list->last = pNewNode;
    list->curr = pNewNode;
    list->numberItems++;
  }
  else {
    pNewNode->next = list->first;
    list->first->prev = pNewNode;

    list->first = pNewNode;
    list->curr = pNewNode;
    list->numberItems++;
  }
  return 0;
}

/* Add list2 to the end of list1. Current item becomes curr pointer item
 * of list1. list2 does not exist after this function is called.\
 */
void ListConcat(LIST *list1, LIST *list2) { 
  if (list1 == NULL || list2 == NULL) {
    printf("Error in procedure ListConcat: invalid parameter\n");
    return;
  }


  if (list1->last != NULL) {
    list1->last->next = list2->first;
  }
  if (list2->first != NULL) {
    list2->first->prev = list1->last;
  }
  list1->last = list2->last;


  list1->numberItems += list2->numberItems;
  FreeListMem(list2);
  return;
}