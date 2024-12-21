# 
# Lab 2 Fall 2020 makefile starting point
#
# inspired by the makefile for UBC pthreads
# Maintained by Dwight Makaroff, University of Saskatchewan
# Last modified September 19, 2020
# ADD YOUR ID HERE FOR YOUR MODS
##
#
CC     = gcc   


#### Figure out how to get the right build architecture

PLATFORM = $(shell uname -s)
ARCH = $(shell uname -m)

CC=gcc 
CPPFLAGS=-std=gnu90 -Wall -pedantic -g -D$(ARCH)
CFLAGS= -g 

.PHONY: all clean

### Different target if you are cross-compiling for different architecture
### You will need to change this target when you want to
### build on the arm architecture for Part C
### 
### and set the cross compiler appropriately
### and set the build directory appropriately,
### should you so choose
###

### CROSS_COMPILE

### If you choose to use the build structure, define this
### completely for different architectures.

BUILD=./build

### if on x86_64 then targets and builds are
### appropriately named with x86_64
### if on arm, then do likewise
### Remember to place your EXECUTABLE
### in the main directory, not in a subdirectory
### so EXECUTABLES will need distinct names

all: $(BUILD) program

$(BUILD):
	mkdir -p $(BUILD)

program: $(BUILD)/program.o
	$(CC) -o program $(BUILD)/program.o

$(BUILD)/program.o: program.c
	$(CC) $(CFLAGS) -c program.c -o $(BUILD)/program.o -I.

clean:
	rm -rf $(BUILD) program


CPP = /usr/bin/cpp

# change these if your application code is not in the same
# directory as the pthreads library.
INCLUDEDIR=.
LIBDIR=lib
MYINCLUDEDIR=.
MYLIBDIR=.

app:    app.o $(LIBDIR)/$(PLATFORM)$(ARCH)/libpthreads.a 
	$(CC) app.o -L$(LIBDIR)/$(PLATFORM)$(ARCH) -lpthreads -L$(MYLIBDIR) -lmylib -o app

app.o: app.c $(MYINCLUDEDIR)/lib.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c app.c -I$(MYINCLUDEDIR) -I$(INCLUDEDIR)
