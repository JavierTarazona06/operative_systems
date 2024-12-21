/*
NAMEs: Javier Andres Tarazona Jimenez, Steven Baldwin
NSIDs: elr490, sjb956
Student Numbers: 11411898, 11300210
*/

#include <rtthreads.h>
#include <time.h>

void myerror(char *error_message);

/* Threads */
#define SLEEPMAX 6
#define STKSIZE 10024

extern RttThreadId *threadIDs;

/* Memory Space */
/*#define VIRTUAL_SIZE 4096*/ /*4096*/
extern int VIRTUAL_SIZE;
/*#define PHYSICAL_SIZE 1024*/ /*1024*/
extern int PHYSICAL_SIZE;

/*#define PAGESIZE 128*/
extern int PAGESIZE;
/*#define FRAME_SIZE 128*/
extern int FRAME_SIZE;
/* 128 */

/*#define NUM_PHYSICAL_FRAMES PHYSICAL_SIZE / FRAME_SIZE*/
extern int NUM_PHYSICAL_FRAMES;
/*#define NUM_VIRTUAL_PAGES VIRTUAL_SIZE / PAGESIZE*/
extern int NUM_VIRTUAL_PAGES;

/* Pages Management */

extern int replace_algorithm;

typedef struct frame_s{
    long int process_ID;
    unsigned int reference; /* Page has been access  ed ? */
    unsigned int dirty; /* Page has been modified ? */
    unsigned int va; /* The virtual address that is pointing */
} frame_s;

extern frame_s *memory;

#define READ_WRITE_SIZE 4

/* Zipf Number Generator */
#define ZIPF_EXPO 1.2


/* Report */

typedef struct metrics{
    unsigned int total_pagefaults;
    double page_faults_per_second;
    unsigned int start_time;
    unsigned int end_time;
    int total_time;
    int read_request;
    int write_request;
    int pagefau_per_readwrite_req;
    char *theReport;
} metrics;

extern metrics my_metrics;

void append(char **original, const char *toAppend);

