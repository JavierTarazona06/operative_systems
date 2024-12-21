#NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
#NSID: elr490, sjb956
#Student Number: 11411898, 

#
# Base
CC = gcc
CFLAGS = -g
CPPFLAGS = -std=gnu90 -Wall -Wextra -pedantic
OBJDR_A = build/obj/a
LIBDR_A = build/lib/a
BINDR_A = build/bin/a
OBJDR_C = build/obj/c
LIBDR_C = build/lib/c
BINDR_C = build/bin/c

UNM := $(shell uname -s)

ifeq ($(UNM), Linux)

OS = linux

else

OS = windows

endif


ifeq ($(OS), windows)

#------------- Part A1 ------------

all: PartA.1.Skeleton

${OBJDR_A}/PartA.1.Skeleton.o: PartA.1.Skeleton.c
	mkdir -p ${OBJDR_A}
	${CC} ${CFLAGS} ${CPPFLAGS} -c PartA.1.Skeleton.c -o ${OBJDR_A}/PartA.1.Skeleton.o
	
PartA.1.Skeleton: ${OBJDR_A}/PartA.1.Skeleton.o
	${CC} ${CFLAGS} -o PartA.1.Skeleton ${OBJDR_A}/PartA.1.Skeleton.o
	

#----------------- Part C  ----------
else

all: mytestlist

${OBJDR_C}/list_adders.o: list_adders.c list.h
	mkdir -p ${OBJDR_C}
	${CC} ${CFLAGS} ${CPPFLAGS} -c list_adders.c -o ${OBJDR_C}/list_adders.o

${OBJDR_C}/list_movers.o: list_movers.c list.h
	${CC} ${CFLAGS} ${CPPFLAGS} -c list_movers.c -o ${OBJDR_C}/list_movers.o

${OBJDR_C}/list_removers.o: list_removers.c list.h
	${CC} ${CFLAGS} ${CPPFLAGS} -c list_removers.c -o ${OBJDR_C}/list_removers.o

liblist.a: ${OBJDR_C}/list_adders.o ${OBJDR_C}/list_movers.o ${OBJDR_C}/list_removers.o
	mkdir -p ${LIBDR_C}
	ar rcs ${LIBDR_C}/liblist.a ${OBJDR_C}/list_adders.o ${OBJDR_C}/list_movers.o ${OBJDR_C}/list_removers.o

mytestlist: mytestlist.c liblist.a
	${CC} ${CFLAGS} -o mytestlist mytestlist.c ${LIBDR_C}/liblist.a
	
endif

clean:
	rm -rf build/ PartA.1.Skeleton mytestlist
