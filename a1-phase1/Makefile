#NAME: Javier Andres Tarazona Jimenez, Nahian Sajid 
#NSID: elr490, Zas742
#Student Number: 11411898, 11309563*/

# Base
CC = gcc
CFLAGS = -g
CPPFLAGS = -std=gnu90 -Wall -Wextra -pedantic
OBJDR_A = build/obj/a
LIBDR_A = build/lib/a
BINDR_A = build/bin/a

${OBJDR_A}/PartA.1.Skeleton.o: PartA.1.Skeleton.c
	mkdir -p ${OBJDR_A}
	${CC} ${CFLAGS} ${CPPFLAGS} -c PartA.1.Skeleton.c -I -o ${OBJDR_A}/PartA.1.Skeleton.o
	
PartA.1.Skeleton: ${OBJDR_A}/PartA.1.Skeleton.o
	${CC} ${CFLAGS} -o PartA.1.Skeleton ${OBJDR_A}/PartA.1.Skeleton.o
	
clean:
	rm -rf build/ PartA.1.Skeleton
