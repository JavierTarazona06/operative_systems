
/* @author Kernighan/Ritchie
 * @modified by: Dwight Makaroff
 * @date: July 2023
 * @purpose: review of CMPT 214 programming style and
 * debugging skills
 */

/*
 * qsort: sort v[left]...v[right] into increasing order.

 * The array v is void *, but from the calling program we see that
 * these are strings.
 */

#include <qsort.h>

void myQsort(void *v[], int left, int right, Comparator comp)
{
    int index, last;


    if (left >= right)  
        return;

    (*swap)(v, left, (left + right)/2);
    last = left;

    for (index = left+1; index < right; index++)
      {
	if ((*comp)(v[index],v[left]) < 0)
	  (*swap)(v, ++last, index);
      }
           
    (*swap)(v, left, last);
    myQsort(v, left, last-1, comp);
    myQsort(v, last+1, right, comp);
}
