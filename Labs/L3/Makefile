# NAME: Javier Andres Tarazona Jimenez, Thomas Brown, Tianze Kuang
#NSID: elr490, vwg123, wde364
#Student Number: 11411898, 11332966, 11352826

#CMPT 332 Term 1 2024

#Lab 3

# Base
CC = gcc
CFLAGS = -g
CPPFLAGS = -std=gnu90 -Wall -Wextra -pedantic
OBJDR = build/obj/
LIBDR = build/lib/
BINDR = build/bin/
BASE_PTHREADLB = /student/cmpt332/pthreads/lib
PTHREADLB_X = ${BASE_PTHREADLB}/Linuxx86_64
STANDARDS = /student/cmpt332/pthreads


all : Lab3 Lab3_test

${OBJDR} :
	mkdir -p ${OBJDR}

${OBJDR}/Lab3.o: Lab3.synchproblem.c | ${OBJDR}
	${CC} ${CFLAGS} ${CPPFLAGS} -o ${OBJDR}/Lab3.o -I. \
	-I${STANDARDS} -c Lab3.synchproblem.c

Lab3: ${OBJDR}/Lab3.o
	${CC} ${CFLAGS} ${OBJDR}/Lab3.o \
	-L${PTHREADLB_X} -lpthreads -o Lab3
	
${OBJDR}/Lab3_test.o: Lab3.testsynchproblem.c | ${OBJDR}
	${CC} ${CFLAGS} ${CPPFLAGS} -o ${OBJDR}/Lab3_test.o -I. \
	-c Lab3.testsynchproblem.c

Lab3_test: ${OBJDR}/Lab3_test.o
	${CC} ${CFLAGS} ${OBJDR}/Lab3_test.o \
	-o Lab3_test

clean:
	rm -rf build/ Lab3 Lab3_test
