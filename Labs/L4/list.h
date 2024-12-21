/*#NAME: Javier Andres Tarazona Jimenez
#NSID: elr490
#Student Number: 11411898

#CMPT 332 Term 1 2024

#Lab 4*/


#include <stdio.h>

typedef struct node
{
  struct node *next;
  struct node *prev;
  void *item;
} NODE;

typedef struct HEAD
{
  int count;
  NODE *first;
  NODE *last;
  NODE *current;
  struct HEAD *nfree;
} LIST;

#define BEFORE (NODE *)1
#define AFTER  (NODE *)2

LIST *ListCreate(void);
     /* makes a new, empty list, and returns its reference on success. 
	Returns a NULL pointer on failure. */ 
int ListCount(LIST *L);
     /* returns the number of items in list.  */
void *ListFirst(LIST *L);
     /* returns a pointer to the first item in list and makes the first item 
	the current item.  */
void *ListLast(LIST *L);
     /* returns a pointer to the last item in list and makes the last item 
	the current one.  */
void *ListNext(LIST *L);
     /* advances list's current item by one, and returns a pointer to the 
	new current item. If this operation advances the
	current item beyond the end of the list, a NULL pointer is returned. */
void *ListPrev(LIST *L);
     /* backs up list's current item by one, and returns a pointer to the 
	new current item. If this operation backs up the current item beyond 
	the start of the list, a NULL pointer is returned.  */
void *ListCurr(LIST *L);
     /* returns a pointer to the current item in list. */
int ListAdd(LIST *L, void *item);
     /* adds the new item to list directly after the current item, and makes 
	item the current item. If the current pointer is before the start of 
        the list, the item is added at the start. If the current pointer is 
        beyond the end of the list, the item is added at the end.
	Returns 0 on success, -1 on failure. */
int ListInsert(LIST *L, void *item);
     /* adds item to list directly before the current item, and makes the 
	new item the current one. If the current pointer is before the start 
        of the list, the item is added at the start. If the current pointer 
        is beyond the end of the list, the item is added at the end. 
	Returns 0 on success, -1 on failure. */
int ListAppend(LIST *L, void *item);
     /* adds item to the end of list, and makes the new item the current one. 
	Returns 0 on success, -1 on failure.  */
int ListPrepend(LIST *L, void *item);
     /* adds item to the front of list, and makes the new item the current one.
	Returns 0 on success, -1 on      failure. */
void *ListRemove(LIST *L);
     /* Return current item and take it out of list. 
	Make the next item the current one.  */
void ListConcat(LIST *list1, LIST *list2);
     /* adds list2 to the end of list1. The current pointer is set to the 
	current pointer of list1. List2 no longer exists after the operation.
     */


void ListFree(LIST *L, void  (*itemFree)(void *));
     /* delete list. itemFree is a pointer to a routine that frees an item. 
	It should be invoked (within ListFree) as: (*itemFree)(itemToBeFreed); 
     */


void *ListTrim(LIST *L);
     /* Return last item and take it out of list. Make the new last item the 
	current one.  */


void *ListSearch(LIST *L, int (*comparator) (void *, void *), 
		 void *comparisonArg);
     /* searches list starting at the current item until the end is reached or
     a match is found. In this context, a match is determined by the
     comparator parameter. This parameter is a pointer to a routine that 
     takes as its first argument an item pointer, and as its second argument 
     comparisonArg. Comparator returns 0 if the item and comparisonArg don't 
     match, or 1 if they do. Exactly what constitutes a match is up to the 
     implementor of comparator. If a match is found, the current pointer is 
     left at the matched item and the pointer to that item is returned. If 
     no match is found, the current pointer is left beyond the end of the
     list and a NULL pointer is returned.  */

