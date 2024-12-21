#NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
#NSID: elr490, sjb956
#Student Number: 11411898, 11300210

#CMPT 332 Term 1 2024

#Assignment 2

#
# Base
CC = gcc
CFLAGS = -g
CPPFLAGS = -std=gnu90 -Wall -Wextra -pedantic
OBJDR = build/obj
LIBDR = build/lib
BINDR = build/bin
OBJDR_list = build/obj/list
LIBDR_list = build/lib/list
RTTHREADS = /student/cmpt332/rtt/lib/Linuxx86_64
RTTHREADINC = /student/cmpt332/rtt/include
RTT = /student/cmpt332/rtt
RPC = /usr/include/tirpc

all: s-chat_t

#------------ S-chat ------

s-chat_t: makeDirS s-chat hostname

makeDirS:
	mkdir -p ${OBJDR}
	mkdir -p ${LIBDR}

${OBJDR}/keyboard_mang.o: keyboard_mang.c
	${CC} ${CFLAGS} ${CPPFLAGS} -I. -I${RTTHREADINC} -I${RTT} \
	-I${RPC} -c keyboard_mang.c -o ${OBJDR}/keyboard_mang.o

s-chat: ${OBJDR}/keyboard_mang.o
	${CC} ${CFLAGS} -o s-chat ${OBJDR}/keyboard_mang.o \
	-L${RTTHREADS} -lRtt -ltirpc -lRttUtils


hostname: gethost.c
	gcc get_hostname.c -o get_hostname
	
clean:
	rm -rf build/ s-chat
	
