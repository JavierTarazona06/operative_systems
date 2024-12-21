/*NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
 *NSID: elr490, sjb956
 *Student Number: 11411898, 11300210
*/

#include <stdio.h>
#include <monitor.h>
#include <stdlib.h>
#include <os.h>
#include <standards.h>
#include <list.h>
#include <unistd.h>


int mutex;

LIST **condLists;
int *condSemaphores;

LIST *entranceQ;
int entranceSemaphore;
LIST *prioQ;
int prioSemaphore;

/*
Initializes the monitor to handle numConds number of conditionals.

Vars:

mutex: This mutex locks the entire monitor.

CondLists: A list of lists for each cond.
    Each sublist holds the pids of every process waiting on the
    corresponding conditional.

entranceQ: This is a queue that will hold all the processes waiting
for entrance to the monitor.

prioQ: Adhering to the lab4 design, This queue will hold processes 
that should be attended to before the entrance queue. A process that
has signaled another will be put here so it will be attended to first.
This queue could also be used in the future to make a priority system.

Each queue (conds, entrance, and prio) also have thier own semaphores
which are used to govern entrance to its associated waiting list.

*/
void MonInit(int numConds) {
    int i;

    mutex = NewSem(1);
    
    condLists = (LIST **)malloc(numConds * sizeof(LIST *));
    condSemaphores = (int *)malloc(numConds * sizeof(int));

    entranceQ = ListCreate();
    entranceSemaphore = NewSem(0);
    prioQ = ListCreate();
    prioSemaphore = NewSem(0);

    for (i = 0; i < numConds; i++) {
        condLists[i] = ListCreate();
        condSemaphores[i] = NewSem(0);
    }
}


/*
This is the entrance to the monitor.

It will attempt to allow the entering process to enter immediately.

If that fails, it will instead add the process that wants to enter to the
entrance queue and then release the monitor to deal with something else.

Once it's able to enter, it will acquire the monitor lock.
*/
void MonEnter() {
    if (P(mutex) != 0) {
        pid_t pid = MyPid();
        ListAppend(entranceQ, &pid);
        V(mutex);
        P(entranceSemaphore);
        P(mutex);
    }
}


/*
MonLeave is called when a process wants to leave the monitor.

Since something is leaving, the monitor is now available to do more work
so we will bring in a new process. First we will check the prio queue 
since the point is that it has priority, then we will check the entrance 
queue.

If nothing is waiting to enter the monitor in either queue, the monitor
will unlock, and all work is done.

*/
void MonLeave() {
    if (ListCount(prioQ) > 0) {
        ListTrim(prioQ);
        V(prioSemaphore);
    }
    else if (ListCount(entranceQ) > 0) {
        ListTrim(entranceQ);
        V(entranceSemaphore);
    }
    
    V(mutex);
}

/*
MonWait will add the process that needs to wait to the correct wait list.
This is how the monitor will monitor all waiting processes.

After adding to the wait list the monitor will unlock as it is done addressing
this process until the conditional becomes available at which point it will 
reacquire the lock.

Since UBC semaphores are FIFO, I am able to add and remove to the cond lists
in FIFO order to keep the waiting lists updated and correct.
*/
void MonWait(int condIndex) {
    pid_t pid = MyPid();
    ListAppend(condLists[condIndex], &pid);

    V(mutex);
    P(condSemaphores[condIndex]);
    P(mutex);
}

/*
Monsignal will wake up processes from waiting lists when thier conditionals
become available.

First get the correct condlist given by condIndex.

Then free from the waiting list, the most recent process waiting,
and have it resume.

Then if that happens, put the signaling process into the prio queue
and have it wait there until the monitor is ready to return to it and serve
it again.
*/
void MonSignal(int condIndex) {
    LIST *condList;
    
    if (ListCount(condLists[condIndex]) > 0) {
        condList = (condLists[condIndex]);
        ListTrim(condList);
        V(condSemaphores[condIndex]);
    
        pid_t pid = MyPid();
        ListAppend(prioQ, &pid);
        V(mutex);
        P(prioSemaphore);
        P(mutex);
    }
}
