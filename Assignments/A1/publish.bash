#!/bin/bash

# Convert all .txt files in the current directory
for file in *.txt; do
    dos2unix "$file"
done

#tar -cvf CMPT332-Assignment1-phase2-group63 \
#Makefile \
#PartC.design.txt PartC.testplan.txt PartC.testresults.txt \
#listlib.c list_removers.c list_movers.c list_adders.c list.h \
#mytestlist.c PartA.1.c PartA.2.c PartA.3.c PartA.4.c \
#PartA.design.txt PartA.testplan.txt PartA.testresults.txt partA.h\
#partB.bash Square.c git-log.txt\

#tar -tvf CMPT332-assignment1-phase3-group63
