/*#NAME: Javier Andres Tarazona Jimenez
#NSID: elr490
#Student Number: 11411898

#CMPT 332 Term 1 2024

#Lab 6*/

#include <stdio.h>
#include "list.h"
#include <stdlib.h>

#include <rtthreads.h>
#include <RttCommon.h>

#include "BestFitMonitor.h"
#include "monitor.h"


/* INITIALIZATION CODE */
#define OKtoAllocate 0
#define numConds  1

/*#define FREE 0
#define OCCUPIED 1*/

int num_iterations, memory_full, free_memory;
int memory_size;

LIST *MemorySpace;

void myerror2(char *error_message){
    printf("ERROR---------> %s", error_message);
    perror(error_message);
    exit(0);
}

int add_newfree_block(int size){
    /*call inside a monitor*/
    int addr1, sz1;
    MemoryBlock * cur_block;

    free_memory += size;
    memory_full = 0;
    memory_size += size;

    cur_block = ListLast(MemorySpace);

    if ((cur_block -> state) == FREE){
        cur_block -> size += size;
    } else {
        addr1 = cur_block -> startaddress;
        sz1 = cur_block -> size;

        cur_block = (MemoryBlock *)RttMalloc(sizeof(MemoryBlock));
        cur_block -> state = FREE;
        cur_block -> size = size;
        cur_block -> startaddress = addr1 + sz1;

        ListAppend(MemorySpace, cur_block);
    }

    return 0;
}

int reduce_iterations(){
    /*This should be call inside the monitor*/

    /*reduce the number of iterations*/
    num_iterations--;

    /*If num_iterations == 0, exit*/
    if (num_iterations == 0){
        printf("Iterations finished\n");
        printf("Final memory Size : %d\n", memory_size);
        exit(0);
    } else {printf("Executions left: %d\n", num_iterations);}

    return 0;
}

int init_memory(int size){
    /*Given the size in int, return the
     * memory space as a list with a
     * memory block of the given size.*/
    MemoryBlock *cur_block;

    /*Create List for Memory space*/
    MemorySpace = ListCreate();

    /*Create a Memory Block with
     * start address in 0 and the given size and state FREE*/
    cur_block = (MemoryBlock *)RttMalloc(sizeof(MemoryBlock));
    cur_block -> startaddress = 0;
    cur_block -> size = size;
    cur_block -> state = FREE;

    /*Append the memory block to the
     * memory space list*/
    ListAppend(MemorySpace, cur_block);

    /*Set memory full in 0*/
    memory_full = 0;

    /*Set free_memory as size*/
    free_memory = size;

    memory_size = size;

    return 0;
}


/* MONITOR PROCEDURES */
int Initialize(int iterations, int memory_size)
{
    int temp;

    /*Initialize Monitor*/
    RttMonInit(numConds);
    printf("Monitor Initialized\n");

    /*Initialize Memory*/
    temp = init_memory(memory_size);
    if (temp != 0) return -1;
    printf("Memory space created\n");

    /*Set num_iterations to the argument*/
    num_iterations = iterations;

    return 0;
}


int BFAllocate(int size){
    int cycles, flag, address_return;
    int i, blocks_count, best_index;
    MemoryBlock *cur_block, *best_block;
    cycles = 0;
    flag = 1;
    address_return = -1;
    /*Return start address of the memory block*/

    while (flag) {
        RttMonEnter();

        /* To avoid deadlock, if the cycles gets
        * repeated 2 times(cycles>1), the size of the whole
        * memory could be increased by the size of the
        * request thread.
            Call add_new_block(size);
        *      */

        if (memory_full) {
            printf("Memory is full, wait until a thread free memory\n");
            RttMonWait(OKtoAllocate);
        } /*else {
            if (cycles > 0){
                printf("Memory is not full, but there is "
                       "no enough space for the req. size\n");
                temp = add_newfree_block(size);
                if (temp!=0) myerror2("AddFreeBlock");
                printf("The memory space was increased by %d size\n", size);
            }
        }*/

        /*Find best block and best index*/
        blocks_count = ListCount(MemorySpace);
        best_index = -1;
        ListFirst(MemorySpace);
        for (i = 0; i < blocks_count; i++){
            cur_block = ListCurr(MemorySpace);
            if ((cur_block -> state) == FREE){
                if ((cur_block -> size) >= size){
                    best_block = cur_block;
                    best_index = i;
                }
            }
            ListNext(MemorySpace);
        }

        /*If we found a best block*/
        if (best_index != -1){

            /*Set flag=0 to don't repeat de cycle again*/
            flag = 0;

            /*Move the list cursor back to the
             * best block found using the best index*/
            ListFirst(MemorySpace);
            for (i = 0; i < best_index; i++){
                ListNext(MemorySpace);
            }

            /*Update Free Memory*/
            free_memory -= size;
            if (free_memory == 0) memory_full = 1;
            printf("Free memory is %d\n", free_memory);

            if (size == (best_block -> size)){
                best_block -> state = OCCUPIED;
                address_return = best_block -> startaddress;
            } else { /*size is < best block size*/
                cur_block = (MemoryBlock *)RttMalloc(sizeof(MemoryBlock));
                cur_block -> state = OCCUPIED;
                cur_block -> size = size;
                cur_block -> startaddress = best_block -> startaddress;

                best_block -> startaddress += size;
                best_block -> size -= size;

                /*Add cur_block to the left of best_block*/
                ListInsert(MemorySpace, cur_block);

                address_return = cur_block -> startaddress;
            }

            printf("Memory allocated of size %d\n", size);
        } else {
            /*We did not find a best block inspite
             * of having free segements. Then, put thread
             * to sleep to try again*/
            cycles++;

            /*It could not find free block*/
            printf("Could not allocate memory, there "
                   "are no adjacent free blocks enough\n");
            reduce_iterations();
            RttMonLeave();
            return -1;
            /*RttExit();
            break;*/
        }

        reduce_iterations();

        RttMonLeave();
    }

    return address_return;
}


int Free(int address){
    int blocks_count, index;
    MemoryBlock *cur_block, *left_block, *right_block;

    RttMonEnter();

    /*Find memory block with given start address*/
    blocks_count = ListCount(MemorySpace);
    ListFirst(MemorySpace);
    for (index = 0; index < blocks_count; index++){
        cur_block = ListCurr(MemorySpace);
        if ((cur_block -> startaddress) == address){
            break;
        }
        ListNext(MemorySpace);
    }

    cur_block -> state = FREE;

    free_memory += cur_block -> size;
    memory_full = 0;
    printf("Free memory increased to %d\n", free_memory);

    if (ListCount(MemorySpace) != 1){
        if (index >= 1){
            left_block = ListPrev(MemorySpace);
            if ((left_block -> state) == FREE){
                cur_block -> size += left_block -> size;
                cur_block -> startaddress = left_block -> startaddress;
                /*Left block is removed*/
                ListRemove(MemorySpace);
            } else {
                ListNext(MemorySpace);
            }
        }
        if ((index <= (ListCount(MemorySpace)-2)) &&
        (ListCount(MemorySpace) != 1)){
            right_block = ListNext(MemorySpace);
            if ((right_block -> state) == FREE){
                cur_block -> size += right_block -> size;
                ListRemove(MemorySpace);
                if (index != (ListCount(MemorySpace)-2)){
                    ListPrev(MemorySpace);
                } else {ListLast(MemorySpace);}
            }
        }

        RttMonSignal(OKtoAllocate);
    }

    reduce_iterations();

    RttMonLeave();

    return 0;
}
