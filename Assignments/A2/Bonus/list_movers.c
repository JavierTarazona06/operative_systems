/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin 
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 1
*/

#include <stdio.h>
#include <list.h>

/* Returns the number of items in list */
int ListCount(LIST *list) 
{
  if (list == NULL) {
    return -1;
  }

  return list->numberItems;
}

/* Returns a pointer to the first item in list.
 * Current item becomes first item.
 */
void *ListFirst(LIST *list) 
{
  if (list == NULL) {
    return NULL;
  }

  list->curr = list->first;
  
  return list->curr->item;
}

/* Returns a pointer to the last item in list.
 * Current item becomes last item.
 */
void *ListLast(LIST *list) 
{
  if (list == NULL) {
    return NULL;
  }

  list->curr = list->last;

  return list->curr->item;
}

/* Advance curr pointer by one forward in list.
 * Returns a pointer to this new current item.
 * If attempting to advance beyond end of list, NULL pointer returned.
 */
void *ListNext(LIST *list) 
{
  if (list == NULL) {
    return NULL;
  }
  if (list->curr->next == NULL) {
    return NULL;
  }
  
  list->curr = list->curr->next;
  /*list->cursorOffset++;*/

  return list->curr->item;
}

/* Move curr pointer by one backward in list.
 * Returns a pointer to this new current item.
 * If attempting to move before the start of list, NULL pointer returned.
 */
void *ListPrev(LIST *list) 
{
  if (list == NULL) {
    return NULL;
  }
  if (list->curr->prev == NULL) {
    return NULL;
  }

  list->curr = list->curr->prev;
  /*list->cursorOffset--;*/

  return list->curr->item;
}

/* Returns a pointer to the current item in list */
void *ListCurr(LIST *list) 
{
  if (list == NULL) {
    return NULL;
  }
  return list->curr->item;
}

/* Searches list starting at curr item until end is reached or match is found.
 * Match is determined by comparator parameter, which is a pointer to a func
 * that takes its first argument the curr pointer and second argument
 * comparisonArg. If match is found, current item is found item and
 * pointer is returned. If no match, curr pointer at list end and NULL pointer
 * returned.
 */
void *ListSearch(LIST *list, int (*comparator)(void *first, void *second), void *comparisonArg)
{
  if (list == NULL || comparator == NULL || comparisonArg == NULL) {
    printf("Error in procedure ListSearch: invalid parameter\n");
    return NULL;
  }

  while (list->curr != NULL) {
    if (comparator(list->curr->item, comparisonArg) == 1) {
      return list->curr->item;
    }
    list->curr = list->curr->next;
  }
  list->curr = list->last;
  
  return NULL;
}