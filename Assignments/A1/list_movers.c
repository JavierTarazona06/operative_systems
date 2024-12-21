/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin 
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 1
*/

#include <stdio.h>
#include <list.h>

/* Returns the number of items in list */
int ListCount(LIST *list) /*done*/
{
  return list->numberItems;
}

/* Returns a pointer to the first item in list.
 * Current item becomes first item.
 */
void *ListFirst(LIST *list) /*done*/
{
  list->curr = list->first;
  list->cursorOffset = 0;
  
  return list->curr->item;
}

/* Returns a pointer to the last item in list.
 * Current item becomes last item.
 */
void *ListLast(LIST *list) /*done*/
{
  list->curr = list->last;

  if (list->numberItems == 0) {
    list->cursorOffset = 0;
  }
  else {
    list->cursorOffset = list->numberItems-1;
  }

  return list->curr->item;
}

/* Advance curr pointer by one forward in list.
 * Returns a pointer to this new current item.
 * If attempting to advance beyond end of list, NULL pointer returned.
 */
void *ListNext(LIST *list) /*done*/
{
  if (list->curr->next == NULL) {
    return NULL;
  }
  
  list->curr = list->curr->next;
  list->cursorOffset++;

  return list->curr->item;
}

/* Move curr pointer by one backward in list.
 * Returns a pointer to this new current item.
 * If attempting to move before the start of list, NULL pointer returned.
 */
void *ListPrev(LIST *list) /*done*/
{
  if (list->curr->prev == NULL) {
    return NULL;
  }

  list->curr = list->curr->prev;
  list->cursorOffset--;

  return list->curr->item;
}

/* Returns a pointer to the current item in list */
void *ListCurr(LIST *list) /*done*/
{
  return list->curr->item;
}

/* Searches list starting at curr item until end is reached or match is found.
 * Match is determined by comparator parameter, which is a pointer to a func
 * that takes its first argument the curr pointer and second argument
 * comparisonArg. If match is found, current item is found item and
 * pointer is returned. If no match, curr pointer at list end and NULL pointer
 * returned.
 */
void *ListSearch(LIST *list, comparator *comparator, void *comparisonArg)
{
  /*if (comparator == NULL || *comparisonArg = NULL) {
    printf("Error in procedure ListSearch: invalid parameter\n");
    return NULL;
  }*/

  int x = 0;
  void *p = &x;
  printf("Got to procedure ListSearch\n");
  return p;
}