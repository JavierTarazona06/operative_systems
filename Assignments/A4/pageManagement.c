/*
Identification:

Author: Jarrod Pas
Modified by students:  Javier Tarazona
		elr490
		11411898
 */

/* Note: code intentionally not commented */


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <math.h>
#include <unistd.h>

#include <defs.h>
#include <rtthreads.h>
#include <RttCommon.h>
#include <pageManagement.h>
#include <list.h>
#include <monitor.h>

frame_s *memory;
int **pageTables;

LIST *clock_frame_numbers;

int numThreads_page;

int frames_assigned = 0;
int frame_num = 0;

void VirtualMemory_Init(int numThreads){
    int i, j;
    int *curPageTable;

    numThreads_page = numThreads;

    /*List of all the page tables for each process*/
    pageTables = (int **)RttMalloc(numThreads * sizeof(int *));

    for (i=0; i<numThreads; i++){
        /* The thread Page Table, The virtual memory*/
        curPageTable = (int *)RttMalloc(NUM_VIRTUAL_PAGES * sizeof(int));
        for (j=0; j<NUM_VIRTUAL_PAGES; j++){
            /* This value is the frame number related to the page number*/
            curPageTable[j] = -1;
        }

        pageTables[i] = curPageTable;
    }
}


/* Initialize Phyiscal memory, virtual memory
 * and global variables of Page Management*/
void Memory_init(int numThreads){
    int i;
    frame_s *current_f;
    RttMonInit(0);

    memory = (frame_s *)RttMalloc(NUM_PHYSICAL_FRAMES * sizeof(frame_s));

    /* Physical memory Creation */
    for (i=0; i<NUM_PHYSICAL_FRAMES; i++){
        current_f =(frame_s *)RttMalloc(sizeof(frame_s));
        current_f->dirty = 0;
        current_f->reference=0;
        current_f->process_ID = -1;
        memory[i] = *current_f;
    }

    /* Queue for the Clock Page Replacement Algo.*/
    clock_frame_numbers = ListCreate();

    VirtualMemory_Init(numThreads);
}



/* Find frame victim using Clock Algorithm */
int find_slot_clock(void) {
    int flag, need_flag;
    int *cur_frame_num;
    frame_s *current_f;

    flag = true; need_flag = true;

    if (frames_assigned  < NUM_PHYSICAL_FRAMES){
        cur_frame_num = (int *)RttMalloc(sizeof(int));
        *cur_frame_num = frames_assigned;
        need_flag = false;
        current_f = &memory[*cur_frame_num];
        ListAppend(clock_frame_numbers, cur_frame_num);
        frames_assigned++;
    }

    while (flag && need_flag){
        ListFirst(clock_frame_numbers);
        cur_frame_num = ListRemove(clock_frame_numbers);
        current_f = &memory[*cur_frame_num];
        if (current_f->reference == true){
            current_f->reference = false;
        } else {
            flag = false;
        }
        ListAppend(clock_frame_numbers, cur_frame_num);
    }

    return *cur_frame_num;
}

/* Find frame victim using Second Chance Algorithm */
int find_slot_second_chance(void) {
    int flag, need_flag;
    int retr_frame_num;
    frame_s *current_f;

    flag = true; need_flag = true;

    if (frames_assigned  < NUM_PHYSICAL_FRAMES){
        need_flag = false;
        current_f = &memory[frames_assigned];
        retr_frame_num = frames_assigned;
        frames_assigned++;
    }

    while (flag && need_flag){
        current_f = &memory[frame_num];
        retr_frame_num = frame_num;
        if (current_f->reference == true){
            current_f->reference = false;
        } else {
            if (current_f->dirty == true){
                current_f->dirty = false;
            } else {
                flag = false;
            }
        }

        if (frame_num == (NUM_PHYSICAL_FRAMES-1)) {
            frame_num = 0;
        } else {
            frame_num++;
        }
    }

    return retr_frame_num;
}

/* Handles a page fault via:
    * method = 0; Clock Algorithm
    * method = 1; Second-chance algorithm.
 * Returns the pointer to the frame slot the victim is in. */
int find_victim_slot(int method) {
    if (method == 0){
        return find_slot_clock();
    } else if (method == 1) {
        return find_slot_second_chance();
    }

    /* Default is Clock */
    return find_slot_clock();
}


/* Translate virtual Address to a physical frame number.
 * It includes the page faults */
int va2fn(unsigned int va, long int myId){
    int page_number;
    int *frame_number;
    frame_s *currFrame;

    page_number = (int)va / PAGESIZE;
    printf("%ld Process. Page number of va :%d is: %d\n", myId,
           va, page_number);

    /* Get process ID */
    if (myId< 0){ myerror("No process ID found!");}

    frame_number = &pageTables[myId][page_number];

    /* There is no a frame assigned to the virtual address yet*/
    if (*frame_number == -1){
        /* Page Fault */
        printf("%ld Process. "
               "New V.A space not mapped...\n", myId);

        my_metrics.total_pagefaults++;

        *frame_number = find_victim_slot(replace_algorithm);
        currFrame = &memory[*frame_number];
        currFrame->process_ID = myId;
        currFrame->reference = true;
        currFrame->dirty = false;
        currFrame->va = va;

        printf("%ld Process. Has initialized V.A with "
               " frame number %d\n", myId, *frame_number);

    /* The virtual address has a frame number*/
    } else {
        currFrame = &memory[*frame_number];
        if (myId != currFrame->process_ID){
            /* Page Fault */

            my_metrics.total_pagefaults++;

            printf("%ld Process. PAGE FAULT. Can not access V.A with "
                   " frame number %d\n", myId, *frame_number);
            *frame_number = find_victim_slot(replace_algorithm);
            currFrame = &memory[*frame_number];
            currFrame->process_ID = myId;
            currFrame->reference = true;
            currFrame->dirty = false;
            currFrame->va = va;
            printf("%ld Process had a page"
                   " replacement and now V.A is set with "
                   " frame number %d\n", myId, *frame_number);
        } else {
            /* The same ID, but the virtual address might be different */

            if ( va != currFrame->va){
                /*The va are different, then page fault*/

                my_metrics.total_pagefaults++;

                printf("%ld Process. PAGE FAULT. Can not access V.A with "
                       " frame number %d because another "
                       " V.A of the same process had claimed it before"
                       "\n", myId, *frame_number);
                *frame_number = find_victim_slot(replace_algorithm);
                currFrame = &memory[*frame_number];
                currFrame->process_ID = myId;
                currFrame->reference = true;
                currFrame->dirty = false;
                currFrame->va = va;
                printf("%ld Process had a page"
                       " replacement and now V.A is set with "
                       " frame number %d\n", myId, *frame_number);
            }
        }
    }

    return *frame_number;
}

/* The actual read*/
int my_read(unsigned int virt_addr, int size, long int myId){
    int *frame_number;
    unsigned int i, start_page, end_page, counts;

    RttMonEnter();

    my_metrics.read_request++;

    printf("%ld Process to read %d Bt on %d\n", myId, size, virt_addr);
    frame_number = (int *)RttMalloc(sizeof(int));

    /* Perform the Read taking into account the size */
    start_page = virt_addr / PAGESIZE;
    end_page = (virt_addr + ( size* READ_WRITE_SIZE )) / PAGESIZE;
    counts = end_page - start_page + 1;

    for (i=0; i < counts; i++){
        *frame_number = va2fn(virt_addr, myId);
        printf("%ld Process. Read: V.A %d was converted to "
               "frame number %d\n",
               myId, virt_addr, *frame_number);
        virt_addr += PAGESIZE;
    }

    RttFree(frame_number);

    RttMonLeave();

    return 0;
}

/* The actual Write */
int my_write(unsigned int virt_addr, int size, long int myId){
    int *frame_number;
    frame_s *cur_frame1;
    unsigned int i, start_page, end_page, counts;

    RttMonEnter();

    my_metrics.write_request++;

    printf("%ld Process to write %d By on v.a %d\n", myId,
           size, virt_addr);

    frame_number = (int *)RttMalloc(sizeof(int));

    /* Perform the Read taking into account the size */
    start_page = virt_addr / PAGESIZE;
    end_page = (virt_addr + ( size* READ_WRITE_SIZE )) / PAGESIZE;
    counts = end_page - start_page + 1;

    for (i=0; i < counts; i++){

        *frame_number = va2fn(virt_addr, myId);
        printf("%ld Process Write: V.A %d was converted to "
               "frame number %d\n",
               myId, virt_addr, *frame_number);

        cur_frame1 = &memory[*frame_number];
        cur_frame1->dirty = true;

        virt_addr += PAGESIZE;
    }

    RttFree(frame_number);

    RttMonLeave();
    return 0;
}

