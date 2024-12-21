# Javiert T Makefile
GCC = gcc -o
FLAGS =  -Wall -Wextra -pedantic -std=gnu90

myQsort: main.o complex.o double.o int.o input.o qsort.o swap.o
	${GCC} myQsort main.o complex.o double.o input.o int.o qsort.o swap.o -lm

input.o: input-routines.c
	${GCC} input.o -c ${FLAGS} input-routines.c 

swap.o: swap.c
	${GCC} swap.o -c ${FLAGS} swap.c

qsort.o: qsort.c qsort.h
	${GCC} qsort.o -c ${FLAGS} qsort.c -I.

complex.o: complexComp.c qsort.h
	${GCC} complex.o -c ${FLAGS} complexComp.c -I.

double.o: doubleComp.c
	${GCC} double.o -c ${FLAGS} doubleComp.c

int.o: intComp.c
	${GCC} int.o -c ${FLAGS} intComp.c

main.o: sortMain.c qsort.h
	${GCC} main.o -c ${FLAGS} sortMain.c -I.

clean:
	rm -f input.o swap.o qsort.o complex.o double.o int.o main.o myQsort
