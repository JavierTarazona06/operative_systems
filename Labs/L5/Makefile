#NAME: Javier Andres Tarazona Jimenez
#NSID: elr490
#Student Number: 11411898

#CMPT 332 Term 1 2024

#Lab 5

.PHONY: all clean

# Base
CC = gcc
CFLAGS = -g
CPPFLAGS = -std=gnu90 -Wall -Wextra -pedantic


all: mkdir sim

mkdir:
	mkdir -p ${OBJDR}


${OBJDR}/sim.o: sim.c
	${CC} ${CFLAGS} ${CPPFLAGS}  \
	-I. -c sim.c \
	-o ${OBJDR}/sim.o




sim: ${OBJDR}/sim.o
	${CC} ${CFLAGS} -o sim ${OBJDR}/sim.o



clean:
	rm -rf build/ reader_writer


