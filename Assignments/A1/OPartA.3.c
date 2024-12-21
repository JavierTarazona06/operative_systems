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
#include <sys/time.h>
#include <stdbool.h>

#include <partA.h>

#define POSIX

/*Threads API and its access, signals management, and time*/
int n_threads;
int *invocation_count;
pthread_t *threads;
int *threads_ids;
struct timeval *begin_times;
bool keep_running = true;


int check_parameters(int n_threads, int deadline, int size);
/* Deadline is in seconds*/
unsigned long int square_handleA3(unsigned long int n);
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

unsigned long int square_handleA3(unsigned long int n){
	int i;
	int index;
	pthread_t thread_id;
	
	if (!keep_running){
			return n;
	}
	
	thread_id = pthread_self();
	index = -1;
	
	for (i=0; i < n_threads; i++){
			if (pthread_equal(thread_id, threads[i])){
					index = i;
					break;
			}
	}
	
	invocation_count[index]++;
	
	/*return square(n, 3);*/
	return 5;
}

unsigned long int square_handleA1(unsigned long int n){
	return n;
}
unsigned long int square_handleA2(unsigned long int n){
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


void *compute_squares(void *arg){
	int size_n;
	int i;
	pthread_t thread_id;
	double elapsed_time;
	int j, index;
	struct timeval ftime;
	
	size_n = *(int *)arg;
	
	for (i = 1 ; i <= size_n; i++){
		if (!keep_running){
				break;
		} else {
			square_handleA3(i);	
		}
	}
	
	index = 0;
	thread_id = pthread_self();	
	for (j=0; j< n_threads; j++){
			if (pthread_equal(thread_id, threads[j])){
				index = j;
				break;
			}
	}
	
	gettimeofday(&ftime, NULL);
	elapsed_time = time_passed(&begin_times[index], &ftime);
	
	printf("%.5f\n", elapsed_time);
	printf("%d\n", invocation_count[index]);
	
	return  0;	
}

int main (int argc, char *argv[]){
	int size_in, deadline;
	int size;
	char *endptr;
	int k;
	int bi = 2;
	
	if (argc != 4){
		printf("Error in procedure main: invalid parameter"
		" %d.\n", argc);
		return -1;
	}
	
	/*Convert strings to int*/
	n_threads = atoi(argv[1]);
	deadline = atoi(argv[2]);
	size_in = strtol(argv[3], &endptr, 10);
	size = size_in +bi - 2;
	if (*endptr != '\0'){
		printf("Invalid size arg> %s\n", argv[3]);
		return -1;
	}
	if (check_parameters(n_threads, deadline, size) != 0){
		return -1;
	}
	
	/*Let's allocate memory for thread handles and parameters 
	 * for the windows program in two dinamically arrays (at runtime)
	 * (threads and they parameters)*/
	threads = malloc(n_threads * sizeof(pthread_t));
	threads_ids = malloc(n_threads * sizeof(int));
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
		gettimeofday(&begin_times[k], NULL);
		
		if (pthread_create(&threads[k], NULL, compute_squares, 
		&size)!=0){
				printf("Error in thread creation");
				return -1;
		}
		/*Linux API function thread creation with:
		 * NULL for default attributes*/
	}
	
	sleep(deadline);
	keep_running = false;
	
	sleep(2);
		
	free(threads);
	free(threads_ids);
	free(invocation_count);
	free(begin_times);
	
	return 0;	
}
