/*
NAMEs: Javier Andres Tarazona Jimenez, Steven Baldwin
NSIDs: elr490, sjb956
Student Numbers: 11411898, 11300210
*/

#include <stdio.h>
#include <rtthreads.h>
#include <RttCommon.h>
#include <stdlib.h>
#include <string.h>

#include <defs.h>
#include <zipf.h>
#include <pageManagement.h>
#include <monitor.h>


double normalization_cte;
int replace_algorithm, numThreads;
RttThreadId *threadIDs;
int my_time;
char fin_addition_txt[1000];
char fin_addition_txt1[1000];
char *report_file_name;

FILE *the_file;

metrics my_metrics;


/* Memory Space */
int VIRTUAL_SIZE;
int PHYSICAL_SIZE;
int PAGESIZE;
int FRAME_SIZE;
int NUM_PHYSICAL_FRAMES;
int NUM_VIRTUAL_PAGES;


void myerror(char *error_message){
    perror(error_message);
    exit(0);
}

RTTTHREAD the_timer(void *arg){

    int temp;
    unsigned int time_execute;
    time_execute = (unsigned int) arg;

    temp = RttSleep(my_time);
    if (temp <0)myerror("Time error\n");

    printf("Time has passed. Killing Threads!!");

    my_metrics.end_time = time_execute;
    /*my_metrics.total_time = (int)(my_metrics.end_time - my_metrics.start_time);*/
    my_metrics.total_time = my_time;

    my_metrics.page_faults_per_second =
            (double)my_metrics.total_pagefaults /
            my_time;

    my_metrics.pagefau_per_readwrite_req =
            (int) my_metrics.total_pagefaults /
                    (
                            my_metrics.read_request +
                            my_metrics.write_request
                            );

    /*snprintf(fin_addition_txt, sizeof(fin_addition_txt),
             "\n"
             "Results of some metrics:\n"
             "Start Time: %u\n"
             "End Time: %u\n"
             "Total Time: %d\n"
             "Total Page Faults: %d\n"
             "Page Faults Per Second: %f\n"
             "Read Requests: %d\n"
             "Write Requests: %d\n"
             "Page faults per read/write request: %d\n",
             my_metrics.start_time, my_metrics.end_time,
             my_metrics.total_time, my_metrics.total_pagefaults,
             my_metrics.page_faults_per_second,
             my_metrics.read_request, my_metrics.write_request,
             my_metrics.pagefau_per_readwrite_req);

    snprintf(fin_addition_txt1, sizeof(fin_addition_txt1),
             "%f %d\n",
             my_metrics.page_faults_per_second,
             my_metrics.pagefau_per_readwrite_req);*/

    /*printf(my_metrics.theReport);
    printf(fin_addition_txt);*/
    printf(fin_addition_txt1);
    //char* t1 = ("%f ", my_metrics.page_faults_per_second);


    the_file = fopen(report_file_name, (char *)"a");
    if (the_file == NULL) {
        perror("Error opening file");
    }
    /*fprintf(the_file, my_metrics.theReport);
    fprintf(the_file, fin_addition_txt);*/
    fprintf(the_file, "");
    fprintf(the_file, "%f %d\n", my_metrics.page_faults_per_second, my_metrics.pagefau_per_readwrite_req);
    fclose(the_file);

    exit(0);
}

RTTTHREAD simulate(void *arg)
{
    int to_write, sleep;
    unsigned int virtual_addr;
    long myId;
    myId = (long) arg;

    for(;;)
    {
        printf("%ld Process Started\n", myId);

        to_write = rand() % 2;
        printf("%ld Process going to write? %d\n", myId, to_write);


        virtual_addr = zipf_virtual_address(normalization_cte);
        printf("%ld Process v.a: %d\n", myId, virtual_addr);

        if (to_write){
            my_write(virtual_addr, 1, myId);
        } else {
            my_read(virtual_addr, 1, myId);
        }

        sleep = rand() % SLEEPMAX;
        printf("%ld Process to sleep: %d\n", myId, sleep);
        RttSleep((int) (sleep));
    }
}


int mainp(int argc, char *argv[]){
    int temp, i;
    RttSchAttr 	attr;
    RttThreadId *cur_thread;


    /*GET Data from input*/
    /* Suggested: ./PartASim 4096 128 1024 0 15 30 report.txt */
    if (argc != 8) {
        printf("Usage is: %s <virtual_size> <page_size>"
               "<physical_size>"
               "<replacement_algo> "
               "<numberThreads> <time_seconds> <report_file_name>\n", argv[0]);
        myerror("Wrongs args.");
    }

    VIRTUAL_SIZE = atoi(argv[1]);
    if (VIRTUAL_SIZE < 0){
        myerror("Wrong virtual size\n");
    }

    PAGESIZE = atoi(argv[2]);
    if ((PAGESIZE < 0)||(PAGESIZE > VIRTUAL_SIZE)){
        myerror("Wrong page size\n");
    }
    FRAME_SIZE = PAGESIZE;

    PHYSICAL_SIZE = atoi(argv[3]);
    if ((PHYSICAL_SIZE < 0)||(PHYSICAL_SIZE > VIRTUAL_SIZE)){
        myerror("Wrong physical size\n");
    }
    if (PAGESIZE > PHYSICAL_SIZE) myerror("Wrong page_size\n");

    NUM_VIRTUAL_PAGES = VIRTUAL_SIZE / PAGESIZE;
    NUM_PHYSICAL_FRAMES = PHYSICAL_SIZE / FRAME_SIZE;


    replace_algorithm = atoi(argv[4]);
    if ((replace_algorithm < 0) || (replace_algorithm > 1)){
        myerror("Wrong replacement Algorithm. 0-Clock."
                "1-Second CHance\n");
    }

    numThreads = atoi(argv[5]);
    if (numThreads < 0){
        myerror("Wrong Number of Threads\n");
    }

    my_time = (double)atoi(argv[6]);
    if (my_time < 0){
        myerror("Wrong Time\n");
    }

    report_file_name = argv[7];

    setbuf(stdout, 0);

    srand(41);
    normalization_cte = get_virtual_normalization_constant();
    Memory_init(numThreads);

    /* Report Initialization */
    my_metrics.total_pagefaults = 0;
    my_metrics.page_faults_per_second = 0;
    my_metrics.start_time = 0;
    my_metrics.read_request = 0;
    my_metrics.write_request = 0;
    my_metrics.theReport = "/*\n"
                           "NAMEs: Javier Andres Tarazona Jimenez, "
                           " Steven Baldwin\n"
                           "NSIDs: elr490, sjb956\n"
                           "Student Numbers: 11411898, 11300210\n"
                           "*/\n\n"
                           "Assignment 4 Part A Option 2\n"
                           "Test Report\n\n";

    printf("Received %d and %d with cte %f\n",
           replace_algorithm,
           numThreads, normalization_cte);

    /*Timer Thread*/
    attr.startingtime = RTTZEROTIME;
    attr.priority = RTTHIGH;
    attr.deadline = RTTNODEADLINE;

    cur_thread = (RttThreadId *)RttMalloc(sizeof(RttThreadId));

    temp = RttCreate(cur_thread, (void(*)()) the_timer, STKSIZE,"0",
                     &my_time,
                     attr, RTTUSR );


    attr.startingtime = RTTZEROTIME;
    attr.priority = RTTNORM;
    attr.deadline = RTTNODEADLINE;

    /*For the IDS of all the threads*/
    threadIDs = (RttThreadId *)RttMalloc(numThreads * sizeof(RttThreadId));

    for (i=0; i<numThreads; i++){
        cur_thread = (RttThreadId *)RttMalloc(sizeof(RttThreadId));
        threadIDs[i] = *cur_thread;

        temp = RttCreate(&threadIDs[i], (void(*)()) simulate, STKSIZE,"1",
                         (void *) i,
                         attr, RTTUSR );
        if (temp == RTTFAILED) perror("RttCreate");
    }

    printf("Simulate processes created\n");

    return(0);
}