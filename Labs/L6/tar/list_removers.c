/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin 
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 1
*/

#include <stdio.h>
#include "list.h"

extern void FreeNodeMem(NODE *nodeToFree);
extern void FreeListMem(LIST *listToFree);

/* Return current item and remove it from list.
 * Current item becomes next item.
 */
void *ListRemove(LIST *list) 
{
  void *pItem;
  NODE *nodeToRemove;

  if (list == NULL) {
    printf("Error in procedure ListRemove: invalid parameter\n");
    return NULL;
  }
  
  if (list->curr == NULL) {
    return NULL;
  }
  
  pItem = list->curr->item;
  

  
  if (list->curr == list->first) {
    list->first = list->curr->next;
  }
  if (list->curr == list->last) {
    list->last = list->curr->prev;
  }
  


  /*link prev and next*/
  if (list->curr->prev != NULL) {
    list->curr->prev->next = list->curr->next;
  }
  if (list->curr->next != NULL) {
    list->curr->next->prev = list->curr->prev;
  }

  nodeToRemove = list->curr;
  

  if (list->curr->next != NULL) {
    list->curr = list->curr->next;
  }
  else {
    list->curr = list->last;
  }

  FreeNodeMem(nodeToRemove);
  list->numberItems--;
  return pItem;
}

/* Delete the list. itemFree points to a function that frees an item. */
void ListFree(LIST *list, void (*itemFree)(void *itemToFree)) 
{
  NODE *pPointerToNewLast;

  if (itemFree == NULL || list == NULL) {
    printf("Error in procedure ListFree: invalid parameter\n");
    return;
  }

  

  while (list->last != NULL) {
    pPointerToNewLast = list->last->prev;

    itemFree(list->last->item);
    list->curr = list->last;
    ListRemove(list);
    list->last = pPointerToNewLast;
    list->curr = list->last;
  }
  list->first = NULL;
  list->numberItems = 0;
  FreeListMem(list);
  return;
}

/* Return last item and remove it from list.
 * Current pointer becomes remaining last item.
 */
void *ListTrim(LIST *list)
{
  void *itemToReturn;

  if (list == NULL) {
    printf("Error in procedure ListTrim: invalid parameter\n");
    return NULL;
  }
  if (list->last == NULL) {
    return NULL;
  }


  itemToReturn = list->last->item;
  list->curr = list->last;
  ListRemove(list);


  /*LIST REMOVE HANDLES UPDATING ITEM COUNT*/
  return itemToReturn;
}