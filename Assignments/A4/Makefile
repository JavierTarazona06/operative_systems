#/*
#NAMEs: Javier Andres Tarazona Jimenez, Steven Baldwin
#NSIDs: elr490, sjb956
#Student Numbers: 11411898, 11300210
#*/

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


all: mkdir PartASim

mkdir:
	mkdir -p ${OBJDR}
	mkdir -p ${LIBDR}

#---------------------------------------------------------------

#---------------------------------------------------------------
# PartASim
#---------------------------------------------------------------

PartASim: list ${LIBDR}/libMonitor.a ${OBJDR}/zipf.o \
${OBJDR}/pageManagement.o ${OBJDR}/PartASim.o
	${CC} ${CFLAGS} \
	-o PartASim \
	${OBJDR}/zipf.o \
	${OBJDR}/pageManagement.o \
	${OBJDR}/PartASim.o \
    -L${LIBDR} -lMonitor -L${LIBDR} -llist \
	-L${RTTHREADS} -lRtt -ltirpc -lRttUtils -lm

${OBJDR}/zipf.o: zipf.c defs.h
	${CC} ${CFLAGS} ${CPPFLAGS} \
	-o ${OBJDR}/zipf.o \
	-c zipf.c \
	-I. -I${RTTHREADINC} -I${RTT} -I${RPC}

${OBJDR}/pageManagement.o: pageManagement.c list.h defs.h
	${CC} ${CFLAGS} ${CPPFLAGS} \
	-o ${OBJDR}/pageManagement.o \
	-c pageManagement.c \
	-I. -I${RTTHREADINC} -I${RTT} -I${RPC}

${OBJDR}/PartASim.o: PartASim.c defs.h monitor.h zipf.h
	${CC} ${CFLAGS} ${CPPFLAGS} \
	-o ${OBJDR}/PartASim.o \
	-c PartASim.c \
	-I. -I${RTTHREADINC} -I${RTT} -I${RPC}

#---------------------------------------------------------------

#---------------------------------------------------------------
#MONITOR
#---------------------------------------------------------------

monitor: ${LIBDR}/libMonitor.a

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


#---------------------------------------------------------------

#---------------------------------------------------------------
#LIB LIST-------------------------------------------------------
#---------------------------------------------------------------

list: ${LIBDR}/liblist.a

${LIBDR}/liblist.a: ${OBJDR}/list_adders.o ${OBJDR}/list_movers.o \
${OBJDR}/list_removers.o ${OBJDR}/listlib.o
	ar rcs ${LIBDR}/liblist.a \
	${OBJDR}/listlib.o \
	${OBJDR}/list_adders.o \
	${OBJDR}/list_movers.o \
	${OBJDR}/list_removers.o

${OBJDR}/listlib.o: listlib.c list.h
	$(COMPILE) listlib.c \
	-I. \
	-o ${OBJDR}/listlib.o

${OBJDR}/list_adders.o: list_adders.c list.h
	$(COMPILE) -c list_adders.c \
	-I. \
	-o ${OBJDR}/list_adders.o

${OBJDR}/list_movers.o: list_movers.c list.h
	$(COMPILE) list_movers.c \
	-I. \
	-o ${OBJDR}/list_movers.o

${OBJDR}/list_removers.o: list_removers.c list.h
	$(COMPILE) list_removers.c \
	-I. \
	-o ${OBJDR}/list_removers.o

#---------------------------------------------------------------
#---------------------------------------------------------------
#---------------------------------------------------------------

clean:
	rm -rf build/ PartASim
