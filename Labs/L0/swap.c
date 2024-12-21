/* swap.c
 * implementation of swap function
 * @author Dwight Makaroff
 * @date: July 2023
 */

void swap(void  *v[], int i, int j)
{
  void *temp;
  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}



