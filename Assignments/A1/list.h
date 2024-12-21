/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin 
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 1
*/

#ifndef LISTLIB
#define LISTLIB

#define MAX_LISTS 1000
#define MAX_NODES 1000

typedef struct NODE {
  void *item;
  struct NODE *next;
  struct NODE *prev;
} NODE;


/*Offset is used to access*/

typedef struct LIST {
  int numberItems;
  int cursorOffset;

  NODE *first;
  NODE *curr;
  NODE *last;
} LIST;

typedef int (*comparator)(void *first, void *second);
typedef void (*itemFree)(void *itemToBeFreed);

/*extern NODE nodeMem[1000];
extern LIST listMem[1000];
extern LIST *listP;*/
void InitListLib();


LIST *ListCreate();
int ListCount(LIST *list);
void *ListFirst(LIST *list);
void *ListLast(LIST *list);
void *ListNext(LIST *list);
void *ListPrev(LIST *list);
void *ListCurr(LIST *list);
int ListAdd(LIST *list, void *item);
int ListInsert(LIST *list, void *item);
int ListAppend(LIST *list, void *item);
int ListPrepend(LIST *list, void *item);
void *ListRemove(LIST *list);
void ListConcat(LIST *list1, LIST *list2);
void *ListTrim(LIST *list);

void ListFree(LIST *list, itemFree *itemFree);
void *ListSearch(LIST *list, comparator *comparator, void *comparisonArg);


#endif
