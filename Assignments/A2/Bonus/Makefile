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
COMPILE = ${CC} ${CFLAGS} ${CPPFLAGS} -c
LINK = ${CC} ${CFLAGS}

OBJDR = build/obj
LIBDR = build/lib
BINDR = build/bin

OBJDR_AL = build/obj/al
LIBDR_AL = build/lib/al
OBJDR_B = build/obj/b
LIBDR_B = build/lib/b
BINDR_B = build/bin/b
BASE_PTHREADLB = /student/cmpt332/pthreads/lib
PTHREADLB_X = ${BASE_PTHREADLB}/Linuxx86_64
STANDARDS = /student/cmpt332/pthreads
OSP = /student/cmpt332/pthreads

BASERTTHREADS = /student/cmpt332/rtt/lib
RTTHREADS = ${BASERTTHREADS}/Linuxx86_64
RTTHREADS_ARM = ${BASERTTHREADS}/Linuxarmv7l
RTTHREADS_PPC = ${BASERTTHREADS}/Linuxppc

RTTHREADINC = /student/cmpt332/rtt/include
RTT = /student/cmpt332/rtt
RPC = /usr/include/tirpc

# For ARM
CROSS_COMPILE_ARM = arm-linux-gnueabihf-
CC_ARM = ${CROSS_COMPILE_ARM}${CC}-10
AR_ARM = ${CROSS_COMPILE_ARM}${AR}
ARCHIC_ARM = arm
PTHREADLB_ARM = ${BASE_PTHREADLB}/Linuxarmv7l

# For PPC
CROSS_COMPILE_PPC = powerpc-linux-gnu-
CC_PPC = ${CROSS_COMPILE_PPC}${CC}
AR_PPC = ${CROSS_COMPILE_PPC}${AR}
ARCHIC_PPC = ppc
PTHREADLB_PPC = ${BASE_PTHREADLB}/Linuxppc


OBJDR_ARM = ${OBJDR}/${ARCHIC_ARM}
BINDR_ARM = ${BINDR}/${ARCHIC_ARM}
LIBDR_ARM = ${LIBDR}/${ARCHIC_ARM}

OBJDR_PPC = ${OBJDR}/${ARCHIC_PPC}
BINDR_PPC = ${BINDR}/${ARCHIC_PPC}
LIBDR_PPC = ${LIBDR}/${ARCHIC_PPC}



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

else

all: makeDirs mytestlist s-chatbonus

makeDirs:
	mkdir -p $(OBJDR_B)
	mkdir -p $(LIBDR_B)
	mkdir -p ${OBJDR}
	mkdir -p ${LIBDR}
	mkdir -p ${OBJDR_ARM}
	mkdir -p ${LIBDR_ARM}
	mkdir -p ${OBJDR_PPC}
	mkdir -p ${LIBDR_PPC}

#------------ -------- S-chat ------
s-chat_t: s-chat s-chat-arm s-chat-ppc

${OBJDR}/keyboard_mang.o: keyboard_mang.c s-chat.h
	${CC} ${CFLAGS} ${CPPFLAGS} -I. -I${RTTHREADINC} -I${RTT} \
	-I${RPC} -c keyboard_mang.c -o ${OBJDR}/keyboard_mang.o

${OBJDR}/udp_mang.o: udp_mang.c s-chat.h
	${CC} ${CFLAGS} ${CPPFLAGS} -I. -I${RTTHREADINC} -I${RTT} \
	-I${RPC} -c udp_mang.c -o ${OBJDR}/udp_mang.o

${LIBDR}/libSChat.a: ${OBJDR}/keyboard_mang.o ${OBJDR}/udp_mang.o
	${AR} rc ${LIBDR}/libSChat.a ${OBJDR}/keyboard_mang.o ${OBJDR}/udp_mang.o

${OBJDR}/s-chat.o: s-chat.c s-chat.h
	${CC} ${CFLAGS} ${CPPFLAGS} -I. \
	-I${RTTHREADINC} -I${RTT} -I${RPC} -c s-chat.c -o ${OBJDR}/s-chat.o

s-chat: ${OBJDR}/keyboard_mang.o ${OBJDR}/udp_mang.o \
${LIBDR}/libSChat.a ${OBJDR}/s-chat.o
	${CC} ${CFLAGS} -o s-chat-linux ${OBJDR}/s-chat.o ${OBJDR}/udp_mang.o \
	${OBJDR}/keyboard_mang.o \
	-L${LIBDR} -lSChat -L. -llist \
	-L${RTTHREADS} -lRtt -ltirpc -lRttUtils
	
#-------SCHAT ARM-------------
	
${OBJDR_ARM}/keyboard_mang.o: keyboard_mang.c s-chat.h
	${CC_ARM} ${CFLAGS} ${CPPFLAGS} -I. -I${RTTHREADINC} -I${RTT} \
	-I${RPC} -c keyboard_mang.c -o ${OBJDR_ARM}/keyboard_mang.o

${OBJDR_ARM}/udp_mang.o: udp_mang.c s-chat.h
	${CC_ARM} ${CFLAGS} ${CPPFLAGS} -I. -I${RTTHREADINC} -I${RTT} \
	-I${RPC} -c udp_mang.c -o ${OBJDR_ARM}/udp_mang.o

${LIBDR_ARM}/libSChat.a: ${OBJDR_ARM}/keyboard_mang.o \
${OBJDR_ARM}/udp_mang.o
	${AR_ARM} rc ${LIBDR_ARM}/libSChat.a ${OBJDR_ARM}/keyboard_mang.o \
	${OBJDR_ARM}/udp_mang.o

${OBJDR_ARM}/s-chat.o: s-chat.c s-chat.h
	${CC_ARM} ${CFLAGS} ${CPPFLAGS} -I. \
	-I${RTTHREADINC} -I${RTT} -I${RPC} -c s-chat.c -o ${OBJDR_ARM}/s-chat.o

s-chat-arm: ${OBJDR_ARM}/keyboard_mang.o ${OBJDR_ARM}/udp_mang.o \
${LIBDR_ARM}/libSChat.a ${OBJDR_ARM}/s-chat.o
	${CC_ARM} ${CFLAGS} -o s-chat-arm ${OBJDR_ARM}/s-chat.o \
	${OBJDR_ARM}/udp_mang.o \
	${OBJDR_ARM}/keyboard_mang.o \
	-L${LIBDR_ARM} -lSChat  \
	-L${LIBDR_ARM} -llist \
	-L${RTTHREADS_ARM} -lRtt -ltirpc -lRttUtils

#--------------------------------


#-------SCHAT PPC-------------
	
${OBJDR_PPC}/keyboard_mang.o: keyboard_mang.c s-chat.h
	${CC_PPC} ${CFLAGS} ${CPPFLAGS} -I. -I${RTTHREADINC} -I${RTT} \
	-I${RPC} -c keyboard_mang.c -o ${OBJDR_PPC}/keyboard_mang.o

${OBJDR_PPC}/udp_mang.o: udp_mang.c s-chat.h
	${CC_PPC} ${CFLAGS} ${CPPFLAGS} -I. -I${RTTHREADINC} -I${RTT} \
	-I${RPC} -c udp_mang.c -o ${OBJDR_PPC}/udp_mang.o

${LIBDR_PPC}/libSChat.a: ${OBJDR_PPC}/keyboard_mang.o \
${OBJDR_PPC}/udp_mang.o
	${AR_PPC} rc ${LIBDR_PPC}/libSChat.a ${OBJDR_PPC}/keyboard_mang.o \
	${OBJDR_PPC}/udp_mang.o

${OBJDR_PPC}/s-chat.o: s-chat.c s-chat.h
	${CC_PPC} ${CFLAGS} ${CPPFLAGS} -I. \
	-I${RTTHREADINC} -I${RTT} -I${RPC} -c s-chat.c -o ${OBJDR_PPC}/s-chat.o

s-chat-ppc: ${OBJDR_PPC}/keyboard_mang.o ${OBJDR_PPC}/udp_mang.o \
${LIBDR_PPC}/libSChat.a ${OBJDR_PPC}/s-chat.o
	${CC_PPC} ${CFLAGS} -o s-chat-ppc ${OBJDR_PPC}/s-chat.o \
	${OBJDR_PPC}/udp_mang.o \
	${OBJDR_PPC}/keyboard_mang.o \
	-L${LIBDR_PPC} -lSChat \
	-L${LIBDR_PPC} -llist \
	-L${RTTHREADS_PPC} -lRtt -ltirpc -lRttUtils

#--------------------------------


#------------ -------- S-chatbonus ------

${OBJDR}/keyboard_mangbonus.o: keyboard_mangbonus.c s-chatbonus.h
	${CC} ${CFLAGS} ${CPPFLAGS} -I. -I${RTTHREADINC} -I${RTT} \
	-I${RPC} -c keyboard_mangbonus.c -o ${OBJDR}/keyboard_mangbonus.o

${OBJDR}/udp_mangbonus.o: udp_mangbonus.c s-chatbonus.h
	${CC} ${CFLAGS} ${CPPFLAGS} -I. -I${RTTHREADINC} -I${RTT} \
	-I${RPC} -c udp_mangbonus.c -o ${OBJDR}/udp_mangbonus.o

${LIBDR}/libSChatbonus.a: ${OBJDR}/keyboard_mangbonus.o ${OBJDR}/udp_mangbonus.o
	${AR} rc ${LIBDR}/libSChatbonus.a ${OBJDR}/keyboard_mangbonus.o ${OBJDR}/udp_mangbonus.o

${OBJDR}/s-chatbonus.o: s-chatbonus.c s-chatbonus.h
	${CC} ${CFLAGS} ${CPPFLAGS} -I. \
	-I${RTTHREADINC} -I${RTT} -I${RPC} -c s-chatbonus.c -o ${OBJDR}/s-chatbonus.o

s-chatbonus: ${OBJDR}/keyboard_mangbonus.o ${OBJDR}/udp_mangbonus.o \
${LIBDR}/libSChatbonus.a ${OBJDR}/s-chatbonus.o
	${CC} ${CFLAGS} -o s-chatbonus ${OBJDR}/s-chatbonus.o ${OBJDR}/udp_mangbonus.o \
	${OBJDR}/keyboard_mangbonus.o \
	-L${LIBDR} -lSChatbonus -L. -llist \
	-L${RTTHREADS} -lRtt -ltirpc -lRttUtils
	
#------------------------------


list: mytestlist list-arm list-ppc

#LIB LIST-------------------------------------------------------

mytestlist: mytestlist.c liblist.a
	$(LINK) -I. -o mytestlist mytestlist.c ${LIBDR_B}/liblist.a

liblist.a: ${OBJDR_B}/list_adders.o ${OBJDR_B}/list_movers.o \
${OBJDR_B}/list_removers.o ${OBJDR_B}/listlib.o
	ar rcs ${LIBDR_B}/liblist.a ${OBJDR_B}/listlib.o \
	${OBJDR_B}/list_adders.o ${OBJDR_B}/list_movers.o \
	${OBJDR_B}/list_removers.o

${OBJDR_B}/listlib.o: listlib.c list.h
	$(COMPILE) listlib.c -I. -o ${OBJDR_B}/listlib.o

${OBJDR_B}/list_adders.o: list_adders.c list.h
	$(COMPILE) list_adders.c -I. -o ${OBJDR_B}/list_adders.o

${OBJDR_B}/list_movers.o: list_movers.c list.h
	$(COMPILE) list_movers.c -I. -o ${OBJDR_B}/list_movers.o

${OBJDR_B}/list_removers.o: list_removers.c list.h
	$(COMPILE) list_removers.c -I. -o ${OBJDR_B}/list_removers.o
#---------------------------------------------------------------

#LIB LIST ARM-------------------------------------------------------
list-arm: ${LIBDR_ARM}/liblist.a

${LIBDR_ARM}/liblist.a: ${OBJDR_ARM}/list_adders.o \
${OBJDR_ARM}/list_movers.o \
${OBJDR_ARM}/list_removers.o \
${OBJDR_ARM}/listlib.o
	${AR_ARM} rcs ${LIBDR_ARM}/liblist.a \
	${OBJDR_ARM}/listlib.o \
	${OBJDR_ARM}/list_adders.o \
	${OBJDR_ARM}/list_movers.o \
	${OBJDR_ARM}/list_removers.o

${OBJDR_ARM}/listlib.o: listlib.c list.h
	${CC_ARM} ${CFLAGS} ${CPPFLAGS} \
	-I. -c listlib.c \
	-o ${OBJDR_ARM}/listlib.o

${OBJDR_ARM}/list_adders.o: list_adders.c list.h
	${CC_ARM} ${CFLAGS} ${CPPFLAGS} \
	-I. -c list_adders.c \
	-o ${OBJDR_ARM}/list_adders.o

${OBJDR_ARM}/list_movers.o: list_movers.c list.h
	${CC_ARM} ${CFLAGS} ${CPPFLAGS} \
	-I. -c list_movers.c \
	-o ${OBJDR_ARM}/list_movers.o

${OBJDR_ARM}/list_removers.o: list_removers.c list.h
	${CC_ARM} ${CFLAGS} ${CPPFLAGS} \
	-I. -c list_removers.c \
	-o ${OBJDR_ARM}/list_removers.o
#---------------------------------------------------------------


#LIB LIST PPC-------------------------------------------------------
list-ppc: ${LIBDR_PPC}/liblist.a

${LIBDR_PPC}/liblist.a: ${OBJDR_PPC}/list_adders.o \
${OBJDR_PPC}/list_movers.o \
${OBJDR_PPC}/list_removers.o \
${OBJDR_PPC}/listlib.o
	${AR_PPC} rcs ${LIBDR_PPC}/liblist.a \
	${OBJDR_PPC}/listlib.o \
	${OBJDR_PPC}/list_adders.o \
	${OBJDR_PPC}/list_movers.o \
	${OBJDR_PPC}/list_removers.o

${OBJDR_PPC}/listlib.o: listlib.c list.h
	${CC_PPC} ${CFLAGS} ${CPPFLAGS} \
	-I. -c listlib.c \
	-o ${OBJDR_PPC}/listlib.o

${OBJDR_PPC}/list_adders.o: list_adders.c list.h
	${CC_PPC} ${CFLAGS} ${CPPFLAGS} \
	-I. -c list_adders.c \
	-o ${OBJDR_PPC}/list_adders.o

${OBJDR_PPC}/list_movers.o: list_movers.c list.h
	${CC_PPC} ${CFLAGS} ${CPPFLAGS} \
	-I. -c list_movers.c \
	-o ${OBJDR_PPC}/list_movers.o

${OBJDR_PPC}/list_removers.o: list_removers.c list.h
	${CC_PPC} ${CFLAGS} ${CPPFLAGS} \
	-I. -c list_removers.c \
	-o ${OBJDR_PPC}/list_removers.o
#---------------------------------------------------------------


#MONITOR--------------------------------------------------------
readerWriterTest: ReaderWriter.o libMonitor.a liblist.a
	$(LINK) -L$(PTHREADLB_X) -lpthreads -I. -o reader_writer_test \
	${OBJDR_B}/ReaderWriter.o ${LIBDR_B}/libMonitor.a ${LIBDR_B}/liblist.a

monitor.o: monitor.c
	$(COMPILE) monitor.c -I. -I$(STANDARDS) -o ${OBJDR_B}/monitor.o

ReaderWriterMonitor.o: reader-writer-monitor.c monitor.h
	$(COMPILE) reader-writer-monitor.c -I. -o ${OBJDR_B}/ReaderWriterMonitor.o

ReaderWriter.o: reader-writer.c reader-writer-monitor.h
	$(COMPILE) reader-writer.c -I. -I$(STANDARDS) -o ${OBJDR_B}/ReaderWriter.o

libMonitor.a: monitor.o ReaderWriterMonitor.o
	ar rcs ${LIBDR_B}/libMonitor.a ${OBJDR_B}/monitor.o \
	${OBJDR_B}/ReaderWriterMonitor.o
#---------------------------------------------------------------

endif


clean:
	rm -rf build/ s-chat-linux s-chat-arm s-chat-ppc mytestlist \
	reader_writer_test s-chatbonus

