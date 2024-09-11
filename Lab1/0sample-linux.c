/* Sample code for Lab 1
 * Dwight Makaroff and Noah Orensa
 * August 2020
 */
#include <stdio.h>
#include <stdlib.h>

#include <standards.h>
#include <os.h>

#include <lab1.h>


#define NUMTHREADS 5
PID  pida, pidb, pidc, pidd, pide;
long counter[NUMTHREADS];

PROCESS myThread(void *param)
{
    PID pid;
    int inner,outer;
    int notUsed;
    
    long *temp, tempvalue;
    long  upperloop;

    temp = (long *) param;
    tempvalue = *temp; /* kind of a cheat because you can't dereference 
			  void */
    pid = MyPid();
    
    printf("pid %ld has temp value of %ld\n", pid, tempvalue);
    
    for (outer=0; outer< tempvalue; outer++)
      {
	upperloop = random();
	printf("pid %d counting for %ld timesteps\n",(int) pid,
	       upperloop);
	for (inner=0;inner<upperloop; inner++) notUsed = myFunc(inner);
	printf("pid %d main loop done %d times\n", (int) pid, outer+1);
      }
    printf("pid %ld exiting %d Final value of notUsed %d\n", pid, outer,
	notUsed);
}

void mainp(int argc, char** argv)
{
/*    int sem; */


  if (argc != 2) 
    {
      printf("Usage: ./sample-linux counter\n");
      exit(1);
    }
  
  counter[0] = atol(argv[1]);
  counter[1] = counter[0]+5;
  counter[2] = 1;
  counter[3] = 4;
  counter[4] = counter[0];
  
  srandom(13);
  setbuf(stdout, 0);
/*    sem = NewSem(0); */
  pida = Create( (void(*)()) myThread,16000, "a", (void *) &counter[0],
		   NORM, USR );
  pidb = Create( (void(*)()) myThread,16000, "b", (void *) &counter[1],
		   NORM, USR );
  pidc = Create( (void(*)()) myThread,16000, "c", (void *) &counter[2],
		   NORM, USR );
  pidd = Create( (void(*)()) myThread,16000, "d", (void *) &counter[3],
		   NORM, USR );
  pide = Create( (void(*)()) myThread,16000, "e", (void *) &counter[4],
		   NORM, USR );
  printf("processes created\n");
}
