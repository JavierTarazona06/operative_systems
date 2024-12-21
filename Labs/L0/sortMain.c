/* main program for qSort
 * @author: Kernighan/Ritchie
 * @date: 1978
 * @modified by: Dwight Makaroff
 * July 2023
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <qsort.h>

enum sType 
  {
    STRING, INTEGER, DOUBLE, COMPLEX
  };


#define MAXLINES 100
char *lineptr[MAXLINES];

/* Input: program name and additional arg (0 to STRING, 1 to INT, 2 to DOUBLE, 3 to COMPLEX)*/
int main(int argc, char *argv[])
{
  int nlines;
  enum sType sortType = STRING;
  int (*comparing)(void*, void*);

  if (argc != 2)
    {
      perror("Usage: perror. wrong number of arguments");
      return -1;
    }

  sortType = atoi(argv[1]);
  if ((sortType < 0) || (sortType > 3)){
	perror("Usage: perror. wrong sort type selection");
    return -1;
  }
  {
    perror("Usage: perror. wrong number of arguments");
    return -1;
  }
  
  printf("CCCC\n");


  if (sortType == STRING) comparing = (Comparator) strcmp;
  if (sortType == INTEGER) comparing = compareInt;
  if (sortType == DOUBLE) comparing = compareDouble;
  if (sortType == COMPLEX) comparing = compareComplex;
  
  printf("DDDD\n");

  if ((nlines = readlines(lineptr, MAXLINES)) >=0)
    {
      printf("UNSORTED ORDER\n");
      writelines(lineptr, nlines);
      
      myQsort ((void **)lineptr, 0, nlines-1, comparing);

      printf("\nSORTED ORDER \n");
      
      writelines(lineptr, nlines);
      return 0;
    }
  else
    {
      perror("problem with input");
      return 1;
    }
}


  
