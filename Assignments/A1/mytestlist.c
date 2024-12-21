/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin 
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 1
*/

#include <stdio.h>
#include <list.h>
#include <string.h>

void itemFreeDummyFunction(void *itemToBeFreed) {
  return;
}

int intCompare(void *first, void *second) {
  if ((*(int *)first) == (*(int *)second)) {
    return 0;
  }
  else {
    return 1;
  }
}
int stringCompare(void *first, void *second) {
  return strcmp(first, second);
}


int static totalTestsDone = 0;
int static totalTestsPassed = 0;

int Assert(void *pi1, void *pi2, int testid, int (*comparator)(void*, void*)) {
  totalTestsDone++;
  if (pi1 == NULL && pi2 == NULL) {
    printf("test %d failed\n", testid);
    printf("both null\n");
    return 1;
  }
  
  if (pi1 == NULL) {
    printf("test %d failed\n", testid);
    printf("p1 null\n");
    return 1;
  }
  if (pi2 == NULL) {
    printf("test %d failed\n", testid);
    printf("p2 null\n");
    return 1;
  }

  
  /*int i1 = *pi1;
  int i2 = *pi2;*/

  
  if (comparator(pi1, pi2) == 0) {
    totalTestsPassed++;
    return 0;
  }
  else {
    printf("test %d failed\n", testid);
    printf("not equal\n");
    return 1;
  }
}


int main()
{
  int itemA, itemB, itemC, itemD, *pA, *pB, *pC, *pD;
  itemA = 5;
  itemB = 6;
  itemC = 7;
  itemD = 8;
  pA = &itemA;
  pB = &itemB;
  pC = &itemC;
  pD = &itemD;
  
  char *s1, *s2, *s3;
  s1 = "one";
  s2 = "two";
  s3 = "three";



  printf("Beginning tests for LibList.a\n");
  
  LIST *l;
  l = ListCreate();
  LIST *l2;
  l2 = ListCreate();
  LIST *l3;
  l3 = ListCreate();

  /*LIST ADD, LENGTH 1*/
  printf("Testing add function..\n");
  ListAdd(l, pA);
  int *pt1 = (int *)(ListFirst(l));
  Assert(pt1, pA, 1, intCompare);
  pt1 = (int *)(ListLast(l));
  Assert(pt1, pA, 2, intCompare);


  /*LIST ADD, LENGTH 2*/
  ListAdd(l, pB);
  pt1 = (int *)(ListFirst(l));
  Assert(pt1, pA, 3, intCompare);
  pt1 = (int *)(ListNext(l));
  Assert(pt1, pB, 4, intCompare);
  pt1 = (int *)(ListLast(l));
  Assert(pt1, pB, 5, intCompare);

  /*LIST ADD, LENGTH 3*/
  ListFirst(l);
  ListAdd(l, pC);
  pt1 = (int *)(ListFirst(l));
  Assert(pt1, pA, 6, intCompare);
  pt1 = (int *)(ListNext(l));
  Assert(pt1, pC, 7, intCompare);
  pt1 = (int *)(ListNext(l));
  Assert(pt1, pB, 8, intCompare);


  /*LIST INSERT*/
  printf("Testing insert function..\n");
  ListInsert(l2, pA);
  pt1 = (int *)(ListFirst(l2));
  Assert(pt1, pA, 9, intCompare);
  pt1 = (int *)(ListLast(l2));
  Assert(pt1, pA, 10, intCompare);
  ListInsert(l2, pB);
  ListInsert(l2, pC);
  pt1 = (int *)(ListFirst(l2));
  Assert(pt1, pC, 11, intCompare);
  pt1 = (int *)(ListNext(l2));
  Assert(pt1, pB, 12, intCompare);
  pt1 = (int *)(ListNext(l2));
  Assert(pt1, pA, 13, intCompare);


  /*LIST APPEND*/
  printf("Testing append function..\n");
  ListAppend(l2, pD);
  pt1 = (int *)(ListFirst(l2));
  Assert(pt1, pC, 14, intCompare);
  pt1 = (int *)(ListNext(l2));
  Assert(pt1, pB, 15, intCompare);
  pt1 = (int *)(ListNext(l2));
  Assert(pt1, pA, 16, intCompare);
  pt1 = (int *)(ListNext(l2));
  Assert(pt1, pD, 17, intCompare);

  /*LIST PREPEND*/
  printf("Testing prepend function..\n");
  ListPrepend(l, pD);
  pt1 = (int *)(ListFirst(l));
  Assert(pt1, pD, 18, intCompare);
  pt1 = (int *)(ListNext(l));
  Assert(pt1, pA, 19, intCompare);
  pt1 = (int *)(ListNext(l));
  Assert(pt1, pC, 20, intCompare);
  pt1 = (int *)(ListNext(l));
  Assert(pt1, pB, 21, intCompare);

  /*LIST PREV*/
  printf("Testing prev function..\n");
  pt1 = (int *)(ListLast(l));
  Assert(pt1, pB, 22, intCompare);
  pt1 = (int *)(ListPrev(l));
  Assert(pt1, pC, 23, intCompare);
  pt1 = (int *)(ListPrev(l));
  Assert(pt1, pA, 24, intCompare);
  pt1 = (int *)(ListPrev(l));
  Assert(pt1, pD, 25, intCompare);

  /*LIST CURRENT*/
  printf("Testing curr function..\n");
  pt1 = (int *)(ListCurr(l));
  Assert(pt1, pD, 26, intCompare);
  pt1 = (int *)(ListLast(l));
  pt1 = (int *)(ListCurr(l));
  Assert(pt1, pB, 27, intCompare);
  pt1 = (int *)(ListPrev(l));
  pt1 = (int *)(ListCurr(l));
  Assert(pt1, pC, 28, intCompare);



  /*TEST ALTERNATE DATA TYPES*/
  printf("Testing multiple datatypes..\n");
  ListAdd(l3, s2);
  ListAppend(l3, s3);
  ListPrepend(l3, s1);
  char *pc1 = (char *)(ListCurr(l3));
  Assert(pc1, s1, 29, stringCompare);
  pc1 = (char *)(ListNext(l3));
  Assert(pc1, s2, 30, stringCompare);
  pc1 = (char *)(ListNext(l3));
  Assert(pc1, s3, 31, stringCompare);
  



  /*SPECIAL TESTS: ABOVE MAX LISTS AND NODES*/
  /*LISTS:*/
  printf("Testing node and list maximums..\n");
  totalTestsDone += 4;
  int j;
  for (j = 0; j < MAX_LISTS-3; j++) {
    l2 = ListCreate();
  }
  if (l2 == NULL) {
    printf("test 32 failed\n");
  }
  else {
    totalTestsPassed++;
  }

  l2 = ListCreate(); /*break point*/
  if (l2 != NULL) {
    printf("test 33 failed\n");
  }
  else {
    totalTestsPassed++;
  }
  /*ABOVE MAX NODES:*/
  int k;
  int c;
  for (k = 0; k < MAX_NODES-11; k++) {
    c = ListPrepend(l, pD);
  }
  if (c != 0) {
    printf("test 34 failed\n");
  }
  else {
    totalTestsPassed++;
  }

  c = ListPrepend(l, pD); /*break point*/
  if (c != -1) {
    printf("test 35 failed\n");
  }
  else {
    totalTestsPassed++;
  }
  /*----------------------------------------*/




  printf("Total tests ran: %d\nTotal tests passed: %d\n", totalTestsDone, totalTestsPassed);
  







  /* FUTURE TESTS
  list1Count = ListCount(*l);
  list2Count = ListCount(*l2);
  printf("l1: %d, l2: %d\n", list1Count, list2Count); 
  
  
  

  ListPrev(l);
  ListCurr(l); 
  
  ListRemove(l);
  ListConcat(l, l2);
  ListTrim(l);
  
  ListFree(l, itemFreeDummyFunction); make args pointers
  ListSearch(l, comparatorDummyFunction, pA);
  */

  return 0;
}