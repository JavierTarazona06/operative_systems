/* intComp.cd
 * Implementation of comparison function
 * @author Dwight Makaroff
 * @date: July 2023
 */


/* returns -1 if first < second
 * returns 0 if first == second
 * returns 1 if first > second
 */
int compareDouble(void *first, void *second)
{
  /* fill in the details of comparing 2 doubles */
  double f = *(double *)first;
  double s = *(double *)second;
  int sa = f +s;
  
  return sa;
}


