/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin 
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 1
*/

#include <stdio.h>
#include <list.h>

/* Return current item and remove it from list.
 * Current item becomes next item.
 */
void *ListRemove(LIST *list)
{
  /*if (list == NULL) {
    printf("Error in procedure ListRemove: invalid parameter\n");
    return;
  }*/

  int x = 0;
  void *p = &x;
  printf("Got to procedure ListRemove\n");
  return p;
}

/* Delete the list. itemFree points to a function that frees an item. */
void ListFree(LIST *list, itemFree *itemFree)
{
  /*if (list == NULL || itemFree == NULL) {
    printf("Error in procedure ListFree: invalid parameter\n");
    return;
  }*/

  printf("Got to procedure ListFree\n");
}

/* Return last item and remove it from list.
 * Current pointer becomes remaining last item.
 */
void *ListTrim(LIST *list)
{
  /*if (list == NULL) {
    printf("Error in procedure ListTrim: invalid parameter\n");
    return;
  }*/

  int x = 0;
  void *p = &x;
  printf("Got to procedure ListTrim\n");
  return p;
}