/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210
   CMPT 332 Term 1 2024
   Assignment 3
*/
/* CMPT 332 GROUP 63 Change, Fall 2024 */

#include "kernel/types.h"
#include "user.h"

#define NUM_PROCESSES 4
#define TIME_MAX 10
#define SQUARE_COMP_MAX 20
#define MAX_SHARE 20
#define MAX_GROUP 4

int times[NUM_PROCESSES];
int start_time;


/* Time max is in seconds*/

/* We have shares from 1 to 20 and groups from 1 to 4 */
/* Share is 1 lowest priority, 10 is normal and 20 is high priority*/
/* Group Default is 2. 1 is for background task. 3 and 4 are more priority */

int square(int n, int i){
    /*mutex_lock(&mutex_print);
    printf("Process %d is computing square", i);
    mutex_unlock(&mutex_print);*/

    if (n==0){
        return 0;
    } else {
        return square(n-1, i) + n + n - 1;
    }
}


int main() {
    int pid, i, j;
    int time_sleep, compute_square;

    printf("Parent process created\n");
    start_time = uptime();
    printf("Start time is: %d\n", start_time);

    for (i = 0; i < NUM_PROCESSES; i++){
        pid = fork();
        if (pid < 0) {
            printf("Fork failed\n");
            exit(0);
        }

        /*This is for the children - Children execution*/
        if (pid == 0) {
            times[i] = uptime();

            time_sleep = uptime() %TIME_MAX;

            printf("Process %d to sleep %d seconds.\n", i, time_sleep);

            sleep(time_sleep);

            printf("Process %d has woken up\n", i);

            compute_square = uptime() % SQUARE_COMP_MAX;

            printf("Process %d is going to compute square %d times\n",
                   i, compute_square);

            for (j=0; j < compute_square; j++){
                square(uptime()%SQUARE_COMP_MAX, i);
            }

            times[i] = uptime()-times[i];
            printf("Runtime of process %d is %d\n", i, times[i]);
            exit(0);
        }
        sleep(10);
    }

    for (i = 0; i < NUM_PROCESSES; i++) {
        wait(0);
    }

    printf("All processes have finished\n");
    exit(0);
}
