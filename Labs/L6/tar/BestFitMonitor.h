/*#NAME: Javier Andres Tarazona Jimenez
#NSID: elr490
#Student Number: 11411898

#CMPT 332 Term 1 2024

#Lab 6*/

#ifndef FILE_H
#define FILE_H

#define FREE 0
#define OCCUPIED 1

#include "list.h"

extern int memory_size;

typedef struct MemoryBlock {
    int startaddress;
    int size;
    int state; /*Free or occupied*/
} MemoryBlock;

void *Get_Item(LIST* big_list, int index);
int Initialize(int iterations, int memory_size);
int BFAllocate(int size);
/*Return start address of the lock
 * or -1 if could not assign memory*/
int Free(int address);
/*0 for success*/

#endif