# Javier Andres Tarazona Jimenez
# elr490
# 11411898

# Base
CC = gcc
AR = ar
CFLAGS = -g
CPPFLAGS = -std=gnu90 -Wall -pedantic
ARCHIC_X = x86_64
BASE_PTHREADLB = /student/cmpt332/pthreads/lib
PTHREADLB_X = ${BASE_PTHREADLB}/Linuxx86_64
STANDARDS = /student/cmpt332/pthreads

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

# Directory Organization
OBJDR = build/obj
BINDR = build/bin
LIBDR = build/lib

OBJDR_X = ${OBJDR}/${ARCHIC_X}
BINDR_X = ${BINDR}/${ARCHIC_X}
LIBDR_X = ${LIBDR}/${ARCHIC_X}

OBJDR_ARM = ${OBJDR}/${ARCHIC_ARM}
BINDR_ARM = ${BINDR}/${ARCHIC_ARM}
LIBDR_ARM = ${LIBDR}/${ARCHIC_ARM}

OBJDR_PPC = ${OBJDR}/${ARCHIC_PPC}
BINDR_PPC = ${BINDR}/${ARCHIC_PPC}
LIBDR_PPC = ${LIBDR}/${ARCHIC_PPC}

#mkdir -p OBJDR_PPC
#mkdir -p BINDR_PPC
#mkdir -p LIBDR_PPC

# Cross Compiling

# Execute all
every: sample-linux sample-linux-arm sample-linux-ppc

## x86_64
${OBJDR_X}/sample-linux.o: sample-linux.c lab1.h
	mkdir -p ${OBJDR_X}
	${CC} ${CFLAGS} ${CPPFLAGS} -c sample-linux.c -I. -I${STANDARDS} -o ${OBJDR_X}/sample-linux.o

${OBJDR_X}/linux-lib.o: linux-lib.c lab1.h
	${CC} ${CFLAGS} ${CPPFLAGS} -c linux-lib.c -I. -o ${OBJDR_X}/linux-lib.o

${LIBDR_X}/liblinux-lib.a: ${OBJDR_X}/linux-lib.o
	mkdir -p ${LIBDR_X}
	${AR} rc ${LIBDR_X}/liblinux-lib.a ${OBJDR_X}/linux-lib.o

sample-linux: ${OBJDR_X}/sample-linux.o ${LIBDR_X}/liblinux-lib.a
	${CC} ${CFLAGS} -o sample-linux ${OBJDR_X}/sample-linux.o -L${PTHREADLB_X} -lpthreads -L${LIBDR_X} -llinux-lib

## arm
${OBJDR_ARM}/sample-raspi.o: sample-linux.c lab1.h
	mkdir -p ${OBJDR_ARM}
	${CC_ARM} ${CFLAGS} ${CPPFLAGS} -c sample-linux.c -I. -I${STANDARDS} -o ${OBJDR_ARM}/sample-raspi.o
	
${OBJDR_ARM}/raspi-lib.o: linux-lib.c lab1.h
	${CC_ARM} ${CFLAGS} ${CPPFLAGS} -c linux-lib.c -I. -o ${OBJDR_ARM}/raspi-lib.o
	
${LIBDR_ARM}/libraspi-lib.a: ${OBJDR_ARM}/raspi-lib.o
	mkdir -p ${LIBDR_ARM}
	${AR_ARM} rc ${LIBDR_ARM}/libraspi-lib.a ${OBJDR_ARM}/raspi-lib.o
	
sample-linux-arm: ${OBJDR_ARM}/sample-raspi.o ${LIBDR_ARM}/libraspi-lib.a
	${CC_ARM} ${CFLAGS} -o sample-linux-arm ${OBJDR_ARM}/sample-raspi.o -L${PTHREADLB_ARM} -lpthreads -L${LIBDR_ARM} -lraspi-lib

## ppc
${OBJDR_PPC}/sample-ppc.o: sample-linux.c lab1.h
	mkdir -p ${OBJDR_PPC}
	${CC_PPC} ${CFLAGS} ${CPPFLAGS} -c sample-linux.c -I. -I${STANDARDS} -o ${OBJDR_PPC}/sample-ppc.o
	
${OBJDR_PPC}/ppc-lib.o: linux-lib.c lab1.h
	${CC_PPC} ${CFLAGS} ${CPPFLAGS} -c linux-lib.c -I. -o ${OBJDR_PPC}/ppc-lib.o
	
${LIBDR_PPC}/libppc-lib.a: ${OBJDR_PPC}/ppc-lib.o
	mkdir -p ${LIBDR_PPC}
	${AR_PPC} rc ${LIBDR_PPC}/libppc-lib.a ${OBJDR_PPC}/ppc-lib.o
	
sample-linux-ppc: ${OBJDR_PPC}/sample-ppc.o ${LIBDR_PPC}/libppc-lib.a
	${CC_PPC} ${CFLAGS} -o sample-linux-ppc ${OBJDR_PPC}/sample-ppc.o -L${PTHREADLB_PPC} -lpthreads -L${LIBDR_PPC} -lppc-lib


clean:
	rm -rf build/ sample-linux sample-linux-arm sample-linux-ppc
	
	
	
	
#ARCHIC := ${shell uname -m}
#CC = gcc
#ifeq (${ARCHIC}, arm)
#	CC := arm-linux-gnueabi-gcc
#	CROSS_COMPILE = arm-linux-gnueabihf-
#endif
#ifeq (${ARCHIC}, ppc)
#	CC := powerpc-linux-gnu-gcc
#endif

#${OBJDR}:
#	mkdir -p ${OBJDR}
#${LIBDR}:
#	mkdir -p ${LIBDR}
#${BINDR}:
#	mkdir -p ${BINDR}

#ifeq (${ARCHIC}, x86_64)
#	PTHREAD_LB := /student/cmpt332/pthreads/lib/Linuxx86_64
#endif
#ifeq (${ARCHIC}, arm)
#	PTHREAD_LB := /student/cmpt332/pthreads/lib/Linuxarmv7l
#endif
#ifeq (${ARCHIC}, ppc)
#	PTHREAD_LB := /student/cmpt332/pthreads/lib/Linuxppc
#endif

#${BINDR_ARM}/sample-linux-arm: ${OBJDR_ARM}/sample-raspi.o ${LIBDR_ARM}/libraspi-lib.a
#	mkdir -p BINDR_ARM
#	${CC} ${CFLAGS} -o ${BINDR_ARM}/sample-linux-arm ${OBJDR_ARM}/sample-raspi.o -L${PTHREADLB_ARM} -lpthreads -L${LIBDR_ARM} -lraspi-lib
