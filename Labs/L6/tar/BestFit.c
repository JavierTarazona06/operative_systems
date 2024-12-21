/*#NAME: Javier Andres Tarazona Jimenez
#NSID: elr490
#Student Number: 11411898

#CMPT 332 Term 1 2024

#Lab 6*/

#include <stdio.h>
#include <rtthreads.h>
#include <RttCommon.h>
#include <stdlib.h>
#include <time.h>

#include "list.h"
#include "BestFitMonitor.h"

#define STKSIZE 65536

LIST *threads_created;

int number_threads, maxAllocation,
    numberofIterations, threads_killed;
double maxSleepTime, freeProbability;


void myerror(char *error_message){
    printf("---------> %s\n", error_message);
    perror(error_message);
    exit(0);
}

int random_free(double free_probaility){
    /* Given a free probability [0,1],
     * return 0 for not free,
     * 1 for free*/
    int random_binary;

    random_binary = (rand() < (free_probaility * RAND_MAX)) ? 1 : 0;

    return random_binary;
}

RTTTHREAD my_thread(int *arg) {
    int temp, num_thread, size_to_alloc;
    int to_free_block, random_block_index;
    double rand_doub;
    LIST *MemoryBlocksOccupied;
    MemoryBlock *cur_block;

    num_thread = *arg;
    MemoryBlocksOccupied = ListCreate();

    printf("Thread Number %d initialized.\n", num_thread);

    while(1){
        /*Get a random integer number for the size to allocate*/
        size_to_alloc = (rand() % maxAllocation) + 1;
        printf("Thread Number %d wakes up and wants to alloc %d.\n",
               num_thread, size_to_alloc);

        /*Call BFAllocate(int size)*/
        cur_block = (MemoryBlock *)RttMalloc(sizeof(MemoryBlock));
        cur_block -> state = OCCUPIED;
        cur_block -> size = size_to_alloc;

        /*BFAllocate returns the start address of the allocated block*/
        temp = -1;
        while (temp == -1){
            temp = BFAllocate(size_to_alloc);
            if (temp == -1){
                /*Could not find space for thread,
                 * but there is still free space
                 * (Otherwise it would have waited)*/

                /*Try-again solution. The thread will sleep
                 * and try again later hoping that a process
                 * have liberated memory*/
                rand_doub = ((double)rand()/(double)RAND_MAX) *
                        (double)maxSleepTime;
                temp = RttSleep(rand_doub);
                if (temp== RTTFAILED) myerror("Failed Sleep");
                printf("(Avoid Deadlock) Thread %d didn't find "
                       "memory so is "
                       "put to slept for %.2f\n", num_thread, rand_doub);
                /*Kill thread solution*/
                /*printf("-------------------------------------Thread
                 * will be killed\n");
                threads_killed++;
                if (number_threads == threads_killed){
                    printf("Execution finished by killing threads
                    (Deadlock solution)\n");
                    printf("Memory size was: %d\n", memory_size);
                    exit(0);
                } else {
                    RttExit();
                }*/
            }
        }

        cur_block -> startaddress = temp;

        /*Append cur_block to MemoryBlocksOccupied*/
        ListAppend(MemoryBlocksOccupied, cur_block);

        printf("Thread %d allocated size: %d in address %d\n",
               num_thread,
               cur_block -> size, cur_block -> startaddress);

        /*Put thread to sleep a random time
         * from 0 to maxSleepTime seconds*/
        rand_doub = ((double)rand()/(double)RAND_MAX) * (double)maxSleepTime;
        temp = RttSleep(rand_doub);
        if (temp== RTTFAILED) myerror("Failed Sleep");
        printf("Thread %d to slept for %.2f\n", num_thread, rand_doub);

        /*Get random free number */
        to_free_block = random_free(freeProbability);

        if (to_free_block){
            random_block_index = rand() %
                    ListCount(MemoryBlocksOccupied);
            cur_block = Get_Item(MemoryBlocksOccupied,
                                 random_block_index);
            ListRemove(MemoryBlocksOccupied);
            Free(cur_block -> startaddress);
            printf("++++++++++++++++++++ Thread %d have free "
                   "address %d of size %d\n",num_thread,
                   cur_block -> startaddress, cur_block -> size);
        } else {printf("+++++++++++++ Thread %d not sent to "
                       "free\n",num_thread);}

        /*Put thread to sleep a random time
         * from 0 to maxSleepTime seconds*/
        rand_doub = ((double)rand()/(double)RAND_MAX) * (double)maxSleepTime;
        printf("Thread %d to sleep for %.2f\n", num_thread, rand_doub);
        temp = RttSleep(rand_doub);
        if (temp== RTTFAILED) myerror("Failed Sleep");
    }
}

int mainp(int argc, char *argv[]) {
    int temp, i, *num_thread;
    RttSchAttr attr;
    RttThreadId *curr_thread;

    /*GET Data from input*/
    if (argc != 6) {
        printf("Usage is: %s <number_threads> "
               "<maxSleepTime> <maxAllocation> "
               "<freeProbability> <numberofIterations>\n", argv[0]);
        myerror("Wrongs args.");
    }

    number_threads = atoi(argv[1]);
    if (number_threads == 0) number_threads = 4;
    threads_killed = 0;

    maxSleepTime = atof(argv[2]);
    if (maxSleepTime == 0) maxSleepTime = 1.5;

    maxAllocation = atoi(argv[3]);
    if (maxAllocation == 0) maxAllocation = 640;

    freeProbability = atof(argv[4]);
    if (freeProbability == 0) freeProbability = 0.5;

    numberofIterations = atoi(argv[5]);
    if (numberofIterations == 0) numberofIterations = 15;

    printf("Received: \n"
           "N.Threads: %d \n"
           "MaxSleepTime: %.2f \n"
           "MaxAlloc: %d \n"
           "Free Prob: %.2f \n"
           "N. Iterations: %d\n--\n", number_threads,
           maxSleepTime, maxAllocation, freeProbability,
           numberofIterations);


    setbuf(stdout, 0);
    /*Set seed for random number*/
    /*srand(71);*/
    srand(time(NULL));

    /*Initialize BestFitMonitor*/
    Initialize(numberofIterations, maxAllocation);
    printf("BestFitMonitor Initialized\n");

    /*Initialize threads list*/
    threads_created = ListCreate();

    /* Create number_threads threads and
     * add them in thrreads_created*/
    attr.startingtime = RTTZEROTIME;
    attr.priority = RTTNORM;
    attr.deadline = RTTNODEADLINE;

    for (i = 0; i < number_threads; i++){
        curr_thread = (RttThreadId *)RttMalloc(sizeof(RttThreadId));
        num_thread = (int *)RttMalloc(sizeof(int));
        *num_thread = i;

        temp = RttCreate(curr_thread, (void(*)()) my_thread,STKSIZE,"R",
                 num_thread,
                 attr, RTTUSR );
        if (temp == RTTFAILED) myerror("RttCreate");

        ListAppend(threads_created, curr_thread);
    }

    printf("Threads Created!!\nStarting Program Execution...\n");

    return(0);
}

