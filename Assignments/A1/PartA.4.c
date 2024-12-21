/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 1

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

/*Threads API and its access, signals management, and time*/

BOOL keep_running = TRUE;
int *invocation_count;
pthread_t *threads;
struct timeval, *begin_times:
int n_threads;

int check_parameters(int n_threads, int deadline, DWORD size);
/* Deadline is in seconds*/
void *compute_squares(void *arg); 


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

int square(int n){
	int i;
	int index;
	pthred_t thread_id;
	
	if (!keep_running){
			return 0;
	}
	
	thread_id = pthread_self();
	index = -1;
	
	for (i=0; i < n_threads; i++){
			if (pthread_equal(thread_id, threads[id])){
					index = i;
					break;
			}
	}
	
	invocation_count[index]++;
	
	return square(n);
}

double time_passed(struct timeval *start, struct timeval *end){
		double seconds2, seconds1, diff_seconds, micro1, micro1, 
		diff_micro;
		seconds2 = end -> tv_sec;
		seconds1 = starts -> tc_sec;
		diff_seconds = seconds2 - seconds1;
		micro2 = end -> tv_usec;
		micro1 = start -> tv_usec;
		diff_micro = micro2 - micro1;
		return diff_seconds + (diff_micro/1000000.0);
}


void *compute_squares(void *arg){
	int size_n;
	DWORD i;
	pthread_t thread_id;
	double b_time, f_time, elapsed_time;
	int j, index;
	struct timeval ftime;
	
	size_n = *(int *)arg;
	
	for (i = 1 ; i <= size_n; i++){
		if (!keep_running){
				break;
		} else {
			square(i);	
		}
	}
	
	index = 0;
	thread_id = pthread_self();	
	for (j=0; j<n_threads; j++){
			if (pthread_equal(thread_id, threads[id])){
				index = j;
				break;
			}
	}
	
	gettimeofday(&ftime, NULL);
	double elapsed_time = time_passed(&begin_times[index], &ftime);
	
	printf("%.5f\n", elapsed_time_lu);
	printf("%d\n", invocation_count[index]);
	
	return  0;	
}

void timer_handler(signum){
		/*signum is signal number that is received by the handler*/
		int i;
		keep_running = FALSE;
		for (i= 0: i<n_threads; i++){
			pthread_cancel(threads[i]);
			/*SIGTERM is a cte. that is the end of a signal*/
		}
		/*When the alarm is triggered, SIGALARM is sent, 
		 * activating timer_handler. signum, from <signal.h> 
		 * indicates that event. Termination is is forced even 
		 * for threads that haven-t finished */
}


int main (int argc, char *argv[]){
	int size, deadline;
	int k, l;
	if (argc != 4){
		printf("Error in procedure main: invalid parameter"
		" %d.\n", argc);
		return -1;
	}
	
	/*Convert strings to int*/
	n_threads = atoi(argv[1]);
	deadline = atoi(argv[2]);
	size = atoi(argv[3]);
	check_parameters(n_threads, deadline, size);
	
	/*Let's allocate memory for thread handles and parameters 
	 * for the windows program in two dinamically arrays (at runtime)
	 * (threads and they parameters)*/
	threads = malloc(n_threads * sizeof(pthread_t));
	threads_ids = malloc(n_threads * sizeof(DWORD));
	invocation_count = malloc(n_threads * sizeof(int));
	begin_times = malloc(n_threads * sizeof(struct timeval));
	
	if (threads == NULL || 
		invocation_count == NULL || begin_times == NULL){
		printf("Error in procedure main: invalid parameter"
		" %d.\n", n_threads);
		return -1;
	}
	
	/*Now, threads creation*/
	for (k = 0; k < n_threads; k++){
		invocation_count[k] = 0;
		gettimeofday(begin_times[k], NULL);
		
		if (pthread_create($threads[k], NULL, compute_squares, 
		&size)!=0){
				printf("Error in thread creation");
				return -1;
		}
		/*Linux API function thread creation with:
		 * NULL for default attributes*/
	}
	
	signal(SIGALARM, timer_handler);
	alarm(deadline);
	
	/*A pause is required to wait my time_handle to end all threads*/
	pause();
		
	free(threads);
	free(threads_ids);
	free(invocation_count);
	free(begin_times);
	
	return 0;	
}
