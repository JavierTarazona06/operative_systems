

typedef int (*Comparator)(void*, void*);

int compareInt(void*, void*);
int compareDouble(void*, void*);
int compareComplex(void*, void*);


typedef struct {
    double real;
    double imag;
} Complex;

void swap(void  *v[], int i, int j);

int myGetline(char s[], int lim);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

void myQsort(void *v[], int left, int right, Comparator comp);
