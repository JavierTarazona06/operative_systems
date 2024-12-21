#NAME: Javier Andres Tarazona Jimenez
#NSID: elr490
#Student Number: 11411898

#CMPT 332 Term 1 2024

#Lab 7


# Base
CC = gcc
CFLAGS = -g
CPPFLAGS = -std=gnu90 -Wall -Wextra -pedantic
AR = ar
OBJDR = build/obj
LIBDR = build/lib
BINDR = build/bin

COMPILE = ${CC} ${CFLAGS} ${CPPFLAGS} -c
LINK = ${CC} ${CFLAGS}



all: mkdir sim

mkdir:
	mkdir -p ${OBJDR}
	mkdir -p ${LIBDR}


${OBJDR}/sim.o: sim.c
	${CC} ${CFLAGS} ${CPPFLAGS} \
	-o ${OBJDR}/sim.o \
	-c sim.c \
	-lm

sim: ${OBJDR}/sim.o
	${CC} ${CFLAGS} \
	-o sim \
	${OBJDR}/sim.o \
	-lm

clean:
	rm -rf build/ sim
