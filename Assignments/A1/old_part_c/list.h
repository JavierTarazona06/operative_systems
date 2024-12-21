/*NAME: Javier Andres Tarazona Jimenez, Nahian Sajid 
NSID: elr490, Zas742
Student Number: 11411898, 11309563*/

#ifndef LIST_H
#define LIST_H
typedef struct Node {
    void *item;
    struct Node *next;
    struct Node *prev;
} NODE;

typedef struct List {
    NODE *head;
    NODE *tail;
    NODE *current;
    int count;
} LIST;

LIST *ListCreate();
int ListCount(LIST *list);
void *ListFirst(LIST *list);
void *ListLast(LIST *list);
void *ListNext(LIST *list);
void *ListPrev(LIST *list);
void *ListCurr(LIST *list);
int ListAdd (LIST *list, void *item);
int ListInsert(LIST *list, void *item);
int ListAppend(LIST *list, void *item);
int ListPrepend(LIST *list, void *item);
void *ListRemove(LIST *list);
void ListConcat(LIST *list1, LIST *list2);
void ListFree(LIST *list, void (*itemFree)(void *));
void *ListTrim (LIST *list);
void *ListSearch(LIST *list, int(*comparator)(void *, void *),void *comparisonArg);

#endif
