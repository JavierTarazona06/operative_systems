/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 1

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <standards.h>
#include <os.h>

#include <partA.h>

#define TIMER_ID 0

/*Threads API and its access, signals management, and time*/

int *invocation_count;
int *thread_finished;
struct timeval *begin_times, *end_times;
PID *threads_ids;
int n_threads, size_in, deadline;
int form1 = 1;
int form2 = 2;
int size;
int size2;

int check_parameters(int n_threads, int deadline, int size);
/* Deadline is in seconds*/
unsigned long int square_handleA2(unsigned long int n);
int compute_squares(); 
int timer_thread(); 


int check_parameters(int n_threads, int deadline, int size){
	if (n_threads < 1){
		printf("Error in procedure check_parameters: invalid "
		"parameter n_threads %d.\n", n_threads);
		return -1;
	}
	if (deadline < 0) {
		printf("Error in procedure check_parameters: invalid "
		"parameter deadline %d.\n", deadline);
		return -1;
	}
	if (size < 1){
		printf("Error in procedure check_parameters: invalid "
		"parameter size %d.\n", size);
		return -1;
	}
	return 0;
}

unsigned long int square_handleA2(unsigned long int n){
	int i;
	int index;
	PID thread_id;
	
	thread_id = MyPid();
	index = -1;
	
	for (i=0; i < n_threads; i++){
			if (thread_id == threads_ids[i]){
					index = i;
					break;
			}
	}
	
	invocation_count[index]++;
	
	return square(n, 2);
}

unsigned long int square_handleA1(unsigned long int n){
	return n;
}
unsigned long int square_handleA3(unsigned long int n){
	return n;
}

double time_passed(struct timeval *start, struct timeval *end){
		double seconds2, seconds1, diff_seconds, micro1, micro2,
		diff_micro;
		seconds2 = end -> tv_sec;
		seconds1 = start -> tv_sec;
		diff_seconds = seconds2 - seconds1;
		micro2 = end -> tv_usec;
		micro1 = start -> tv_usec;
		diff_micro = micro2 - micro1;
		return diff_seconds + (diff_micro/1000000.0);
}


int compute_squares(){
	int i;
	PID thread_id;
	double elapsed_time;
	int j, index;
	
	for (i = 1 ; i <= size; i++){
		square_handleA2(i);
	}
	
	index = 0;
	thread_id = MyPid();	
	for (j=0; j<n_threads; j++){
			if (thread_id == threads_ids[j]){
				index = j;
				break;
			}
	}
	
	gettimeofday(&end_times[i], NULL);
	elapsed_time = time_passed(&begin_times[index], &end_times[i]);
	
	printf("%.5f\n", elapsed_time);
	printf("%d\n", invocation_count[index]);
	
	return 0;
}

int timer_thread(){
	int i, tmr;
	int elapsed_ticks;
	double elapsed_time;
	
	tmr = ResetETimer(TIMER_ID);
	if (tmr == -1){
			printf("Timer not reset\n");
			return -1;
	}
	
	tmr = StartETimer(TIMER_ID);
	if (tmr == -1){
			printf("Timer not started\n");
			return -1;
	}


	tmr = Sleep(deadline*100);
	
		
	i =0 ;
	for (i=0; i< n_threads; i++){
		if (thread_finished[i] == 0){
			gettimeofday(&end_times[i], NULL);
			elapsed_time = time_passed(&begin_times[i], &end_times[i]);
			thread_finished[i] = 1;
			printf("%.5f\n", elapsed_time);
			printf("%d\n", invocation_count[i]);
			Kill(threads_ids[i]);
			/*printf("------Ihave killed: %ld\n", threads_ids[i]);*/
		}
	}
	
	
	elapsed_ticks = StopETimer(TIMER_ID);
	if (elapsed_ticks == -1) {
		fprintf(stderr, "Error stopping timer.\n");
		exit(-1);
	}
	
	
	return 0;
}

PROCESS proc_thread(void *arg){
	int index, j;
	PID thread_id;
	int argy = *(int *)arg;
	
	if (argy == 1){
		timer_thread();
	} else if (argy == 2){
		compute_squares();
	}
	
	
	if (argy==2){
		index = 0;
		thread_id = MyPid();	
		for (j=0; j<n_threads; j++){
				if (thread_id == threads_ids[j]){
					index = j;
					break;
				}
		}
		thread_finished[index] = 1;
	}
	
	
	if (argy == 1){
		exit(0);	
	} else {
		Pexit();
	}
	
}

void mainp(int argc, char *argv[]){
	int l, k;
	char *endptr;
	char process_name[25];
	int bi = 2;
		
	if (argc != 4){
		printf("Error in procedure main: invalid parameter"
		" %d.\n", argc);
		exit(1);
	}
	
	/*Convert strings to int*/
	n_threads = atoi(argv[1]);
	deadline = atoi(argv[2]);
	size_in = strtol(argv[3], &endptr, 10);
	size = size_in + bi - 2;
	if (*endptr != '\0'){
		printf("Invalid size arg> %s\n", argv[3]);
		exit(-1);
	}
	if (check_parameters(n_threads, deadline, size) != 0){
		exit(1);
	}
	
	size2 = (int) size + bi;
	
	/*Let's allocate memory for thread handles and parameters 
	 * for the windows program in two dinamically arrays (at runtime)
	 * (threads and they parameters)*/
	/*threads_ids = malloc(n_threads * sizeof(PID));
	invocation_count = malloc(n_threads * sizeof(int));
	begin_times = malloc(n_threads * sizeof(struct timeval));
	end_times = malloc(n_threads * sizeof(struct timeval));*/
	threads_ids = (PID *) Malloc(n_threads * sizeof(PID));
	invocation_count = (int *) Malloc(n_threads * sizeof(int));
	begin_times = (struct timeval *) Malloc(n_threads * sizeof(struct timeval));
	end_times = (struct timeval *) Malloc(n_threads * sizeof(struct timeval));
	
	thread_finished = (int *) Malloc(n_threads * sizeof(int));
	l=0;
	for (l=0; l<n_threads; l++){
		thread_finished[l] = 0;
		invocation_count[l] = 0;
		gettimeofday(&begin_times[l], NULL);
		/*Null is for timezone*/
	}
	
	if (!threads_ids || !invocation_count || !begin_times ||
	 !thread_finished){
		printf("Error in procedure main: invalid parameter"
		" %d.\n", n_threads);
		exit(1);
	}
	
	/*Now, threads creation*/
	Create((void(*)()) proc_thread, 2*1024*1024, "parent_process", (void *) &form1, 
		HIGH, USR);
	

	for (k = 0; k < n_threads; k++){
		sprintf(process_name, "square_process%d", k);
		threads_ids[k] = Create((void(*)()) proc_thread, 3*1024*1024, 
		process_name, (void *) &form2, 
		LOW, USR);
		/*Function without in and outs either, 4096 for stack size
		 * the name of my thread, args of process, normal priority
		 * and USeR process, not SYStem */
		
		if (threads_ids[k] == PNUL){
			printf("Error in thread creation");
			exit(1);
		}
		/*UBC function thread creation with:
		 * NULL for default attributes*/
	}
}
