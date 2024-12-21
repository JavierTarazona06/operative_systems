#NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
#NSID: elr490, sjb956
#Student Number: 11411898, 11300210

#
# Base
CC = gcc
CFLAGS = -g
CPPFLAGS = -std=gnu90 -Wall -Wextra -pedantic
OBJDR_A = build/obj/a
LIBDR_A = build/lib/a
BINDR_A = build/bin/a
OBJDR_AL = build/obj/al
LIBDR_AL = build/lib/al
OBJDR_C = build/obj/c
LIBDR_C = build/lib/c
BINDR_C = build/bin/c
BASE_PTHREADLB = /student/cmpt332/pthreads/lib
PTHREADLB_X = ${BASE_PTHREADLB}/Linuxx86_64
STANDARDS = /student/cmpt332/pthreads
OSP = /student/cmpt332/pthreads


UNM := $(shell uname -s)

ifneq ($(findstring NT, $(UNM)),)

OS := windows

else

ifeq ($(UNM), Linux)

OS = linux

else

OS = windows

endif

endif


ifeq ($(OS), windows)

#------------- Part A1 ------------

all: makeDirA1 partA1

makeDirA1:
	mkdir -p ${OBJDR_A}
	
${OBJDR_A}/Square.o: Square.c partA.h
	${CC} ${CFLAGS} ${CPPFLAGS} -c Square.c -o ${OBJDR_A}/Square.o -I.	

${OBJDR_A}/PartA.1.o: PartA.1.c partA.h
	${CC} ${CFLAGS} ${CPPFLAGS} -o ${OBJDR_A}/PartA.1.o -I. -c PartA.1.c
	
partA1: ${OBJDR_A}/Square.o ${OBJDR_A}/PartA.1.o 
	${CC} ${CFLAGS} ${OBJDR_A}/Square.o ${OBJDR_A}/PartA.1.o -o partA1 

else

all: makeDirAl partA2 partA3 mytestlist

#-------- Part A

makeDirAl:
	mkdir -p ${OBJDR_AL}
	
${OBJDR_AL}/Square.o: Square.c partA.h
	${CC} ${CFLAGS} ${CPPFLAGS} -c Square.c -o ${OBJDR_AL}/Square.o -I.	\
	-I${STANDARDS} -I${OSP}
	
# ------- part A.2

${OBJDR_AL}/PartA.2.o: PartA.2.c partA.h
	${CC} ${CFLAGS} ${CPPFLAGS} -o ${OBJDR_AL}/PartA.2.o -I. \
	-I${STANDARDS} -I${OSP} -c PartA.2.c 
	 
	
partA2: ${OBJDR_AL}/PartA.2.o ${OBJDR_AL}/Square.o
	${CC} ${CFLAGS} ${OBJDR_AL}/PartA.2.o ${OBJDR_AL}/Square.o \
	-L${PTHREADLB_X} -lpthreads -o partA2
	
# ------- part A.3

${OBJDR_AL}/PartA.3.o: PartA.3.c partA.h
	${CC} ${CFLAGS} ${CPPFLAGS} -o ${OBJDR_AL}/PartA.3.o -I. \
	-I${STANDARDS} -I${OSP} -c PartA.3.c 
	 
	
partA3: ${OBJDR_AL}/PartA.3.o ${OBJDR_AL}/Square.o
	${CC} ${CFLAGS} ${OBJDR_AL}/PartA.3.o ${OBJDR_AL}/Square.o \
	-L${PTHREADLB_X} -lpthreads -o partA3
	

# ------- part A.4
	
${OBJDR_AL}/PartA.4.o: PartA.4.c partA.h
	${CC} ${CFLAGS} ${CPPFLAGS} -o ${OBJDR_AL}/PartA.4.o -I. \
	-I${STANDARDS} -I${OSP} -c PartA.4.c 
	 
	
partA4: ${OBJDR_AL}/PartA.4.o ${OBJDR_AL}/Square.o
	${CC} ${CFLAGS} ${OBJDR_AL}/PartA.4.o ${OBJDR_AL}/Square.o \
	-L${PTHREADLB_X} -lpthreads -o partA4
	

#----------------- Part C  ----------

mytestlist: makeDir mytestlist.c liblist.a
	${CC} ${CFLAGS} -I. -o mytestlist mytestlist.c ${LIBDR_C}/liblist.a

makeDir:
	mkdir -p $(OBJDR_C)
	mkdir -p $(LIBDR_C)

liblist.a: ${OBJDR_C}/list_adders.o ${OBJDR_C}/list_movers.o \
${OBJDR_C}/list_removers.o ${OBJDR_C}/listlib.o
	ar rcs ${LIBDR_C}/liblist.a ${OBJDR_C}/listlib.o \
	${OBJDR_C}/list_adders.o ${OBJDR_C}/list_movers.o \
	${OBJDR_C}/list_removers.o

${OBJDR_C}/listlib.o: listlib.c list.h
	${CC} ${CFLAGS} ${CPPFLAGS} -c listlib.c -I. -o ${OBJDR_C}/listlib.o

${OBJDR_C}/list_adders.o: list_adders.c list.h
	${CC} ${CFLAGS} ${CPPFLAGS} -c list_adders.c -I. -o \
	${OBJDR_C}/list_adders.o

${OBJDR_C}/list_movers.o: list_movers.c list.h
	${CC} ${CFLAGS} ${CPPFLAGS} -c list_movers.c -I. -o \
	${OBJDR_C}/list_movers.o

${OBJDR_C}/list_removers.o: list_removers.c list.h
	${CC} ${CFLAGS} ${CPPFLAGS} -c list_removers.c -I. \
	-o ${OBJDR_C}/list_removers.o
	
endif

clean:
	rm -rf build/ PartA.1.Skeleton mytestlist partA1 partA2 partA3 partA4
