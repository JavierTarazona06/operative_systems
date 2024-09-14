#ifndef LIST_H
#define LIST_H

#define MAX_LISTS 10
#define MAX_NODES 100

// define node and list structure
typedef struct Node {
    void *item;
    struct Node *next;
    struct Node *prev;
} NODE;


typedef struct list[
    NODE *head;
    NODE *tail;
    NODE *current;
    int count;

] LIST;



// ISNT DONE YET JUST LISTED  "implement the following list manipulation routines"

LIST *ListCreate()
int ListCount
void *ListFirst
void *ListLast
void *listNext
void *ListPrev
void *ListCurr
int ListAdd
int ListInsert
int ListAppend
int ListPrepend
void *ListRemove
void ListConcat
void ListFree
void *ListTrim
void *listSearch

#endif