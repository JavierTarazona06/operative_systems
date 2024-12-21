/* string input routines
 * @author: Kernighan/Ritchie
 * @date: 1978
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 100

int myGetline(char s[], int lim)
{
  int c, i;

  for (i=0;i<lim-1 && (c=getchar()) != EOF && c!='\n'; ++i)
    s[i] = c;
  if (c == '\n')
    {
      s[i] = c;
      ++i;
    }
  return i;
  
}


int readlines(char *lineptr[], int maxlines)
{
  int len, nlines;
  char *p, line[MAXLEN];

  nlines=0;
  while ((len = myGetline(line, MAXLEN)) > 0)
    {
      if (nlines >= maxlines || (p = (char *)malloc(len)) == NULL)
	return -1;
      else 
	{
	  line [len-1] = '\0';
	  memmove(p, line, len);
	  lineptr[nlines++] = p;
	}
    }
  
  return nlines;
}

void writelines(char *lineptr[], int nlines)
{
  int linenum = 0;
  while (nlines-- >0)
    printf("%s\n", *lineptr++);
}
