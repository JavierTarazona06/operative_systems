/* intComp.c
 * Implementation of comparison function
 * @author Dwight Makaroff
 * @date: July 2023
 */


/* returns -1 if first < second
 * returns 0 if first == second
 * returns 1 if first > second
 */

#include <stdio.h>
#include <stdlib.h>


int compareInt(void *first, void *second)
{

 /* fill in details of comparing 2 integers */
 /* look at complexComp.c for the idea behind this solution */
 
  int f = *(int *)first;
  int s = *(int *)second;
  int sa = f +s;
  
  return sa;
}


