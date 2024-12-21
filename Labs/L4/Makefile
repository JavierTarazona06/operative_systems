#NAME: Javier Andres Tarazona Jimenez
#NSID: elr490
#Student Number: 11411898

#CMPT 332 Term 1 2024

#Lab 4

#
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

all: mkdir reader-writer

mkdir:
	mkdir -p ${OBJDR}
	mkdir -p ${LIBDR}

${OBJDR}/monitor.o: monitor.c list.h
	${CC} ${CFLAGS} ${CPPFLAGS} \
	-I. -I${RTTHREADINC} -I${RTT} \
	-I${RPC} -c monitor.c -o ${OBJDR}/monitor.o
	
${LIBDR}/libMonitor.a: ${OBJDR}/monitor.o
	${AR} rc ${LIBDR}/libMonitor.a ${OBJDR}/monitor.o
	

${OBJDR}/reader-writer-monitor.o: reader-writer-monitor.c \
reader-writer-monitor.h monitor.h
	${CC} ${CFLAGS} ${CPPFLAGS} \
	-I. -I${RTTHREADINC} -I${RTT} -I${RPC} -c reader-writer-monitor.c \
	-o ${OBJDR}/reader-writer-monitor.o
	
	
${OBJDR}/reader-writer.o: reader-writer.c reader-writer-monitor.h
	${CC} ${CFLAGS} ${CPPFLAGS}  \
	-I. -I${RTTHREADINC} -I${RTT} -I${RPC} -c reader-writer.c \
	-o ${OBJDR}/reader-writer.o	
	
	
reader-writer: ${LIBDR}/libMonitor.a ${OBJDR}/reader-writer-monitor.o \
${OBJDR}/reader-writer.o 
	${CC} ${CFLAGS} -o reader_writer ${OBJDR}/reader-writer-monitor.o \
	${OBJDR}/reader-writer.o -L${LIBDR} -lMonitor -L. -llist \
	 -L${RTTHREADS} -lRtt -ltirpc -lRttUtils

clean:
	rm -rf build/ reader_writer
