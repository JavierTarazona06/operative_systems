# Tianze Kuang wde364 11352826
# Javier Tarazona elr490 11411898
# Steven Baldwin sjb956 11300210
# Thomas Brown vwg123 11332966
# Lab 5 - CMPT332

CC = gcc
CFLAG = -g
CPPFLAG = -std=gnu90 -Wall -pedantic -Wextra -I.

PathOut = Build

Exe = sim
Path = $(PathOut)/Linux_x86_64
Bin = $(Path)/Bin
Obj = $(Path)/Obj
Lib = $(Path)/Lib

.PHONY : all clean

all : sim

clean :
	rm -rf $(PathOut) $(Exe)

sim : $(Bin)/sim
	ln -sf $(Bin)/sim sim

$(PathOut) $(Obj) $(Lib) $(Bin) :
	mkdir -p $(PathOut) $(Obj) $(Lib) $(Bin)

# Obj file
$(Obj)/sim.o : sim.c | $(Obj)
	$(CC) $(CFLAG) $(CPPFLAG) -c sim.c -o \
	$(Obj)/sim.o -I/student/cmpt332/pthreads

# Link
$(Bin)/sim : $(Obj)/sim.o | $(Bin)
	$(CC) $(Obj)/sim.o -o $(Bin)/sim -L. \
	-L/student/cmpt332/pthreads/lib/Linuxx86_64 \
	-lList \
	-lpthreads
