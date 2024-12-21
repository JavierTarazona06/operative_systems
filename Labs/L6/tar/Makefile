#NAME: Javier Andres Tarazona Jimenez
#NSID: elr490
#Student Number: 11411898

#CMPT 332 Term 1 2024

#Lab 6


# Base
CC = gcc
CFLAGS = -g
CPPFLAGS = -std=gnu90 -Wall -Wextra -pedantic
AR = ar
OBJDR = build/obj
LIBDR = build/lib
BINDR = build/bin
OBJDR_list = build/obj/list
LIBDR_list = build/lib/list
RTTHREADS = /student/cmpt332/rtt/lib/Linuxx86_64
RTTHREADINC = /student/cmpt332/rtt/include
RTT = /student/cmpt332/rtt
RPC = /usr/include/tirpc

COMPILE = ${CC} ${CFLAGS} ${CPPFLAGS} -c
LINK = ${CC} ${CFLAGS}



all: mkdir list BestFit

mkdir:
	mkdir -p ${OBJDR}
	mkdir -p ${LIBDR}


${OBJDR}/monitor.o: monitor.c list.h
	${CC} ${CFLAGS} ${CPPFLAGS} \
	-o ${OBJDR}/monitor.o \
	-c monitor.c \
	-I. -I${RTTHREADINC} -I${RTT} \
	-I${RPC}

${LIBDR}/libMonitor.a: ${OBJDR}/monitor.o
	${AR} rc \
	${LIBDR}/libMonitor.a \
	${OBJDR}/monitor.o


${OBJDR}/BestFitMonitor.o: BestFitMonitor.c \
BestFitMonitor.h monitor.h
	${CC} ${CFLAGS} ${CPPFLAGS} \
	-o ${OBJDR}/BestFitMonitor.o \
	-c BestFitMonitor.c \
	-I. -I${RTTHREADINC} -I${RTT} -I${RPC}


${OBJDR}/BestFit.o: BestFit.c  \
BestFitMonitor.h
	${CC} ${CFLAGS} ${CPPFLAGS} \
	-o ${OBJDR}/BestFit.o \
	-c BestFit.c \
	-I. -I${RTTHREADINC} -I${RTT} -I${RPC}

BestFit: ${LIBDR}/libMonitor.a \
${OBJDR}/BestFitMonitor.o \
${OBJDR}/BestFit.o
	${CC} ${CFLAGS} \
	-o BestFit \
	${OBJDR}/BestFitMonitor.o \
    ${OBJDR}/BestFit.o \
    -L${LIBDR} -lMonitor -L. -llist \
	-L${RTTHREADS} -lRtt -ltirpc -lRttUtils


list: liblist.a

#LIB LIST-------------------------------------------------------

liblist.a: ${OBJDR}/list_adders.o ${OBJDR}/list_movers.o \
${OBJDR}/list_removers.o ${OBJDR}/listlib.o
	ar rcs ${LIBDR}/liblist.a \
	${OBJDR}/listlib.o \
	${OBJDR}/list_adders.o ${OBJDR}/list_movers.o \
	${OBJDR}/list_removers.o

${OBJDR}/listlib.o: listlib.c list.h
	$(COMPILE) listlib.c -I. -o ${OBJDR}/listlib.o

${OBJDR}/list_adders.o: list_adders.c list.h
	$(COMPILE) -c list_adders.c -I. -o ${OBJDR}/list_adders.o

${OBJDR}/list_movers.o: list_movers.c list.h
	$(COMPILE) list_movers.c -I. -o ${OBJDR}/list_movers.o

${OBJDR}/list_removers.o: list_removers.c list.h
	$(COMPILE) list_removers.c -I. -o ${OBJDR}/list_removers.o
#---------------------------------------------------------------


clean:
	rm -rf build/ BestFit