/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 1

*/

#include "partA.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int keep_running = 1;
int *invocation_count;
HANDLE *threads;
int *threads_ids;
DWORD imm_threadid;
/* DWORD is an unsigned 32-bit integer*/
SYSTEMTIME *begin_times;
int n_threads;
int thread_finished = 0;

int check_parameters(int n_threads, int deadline, DWORD size);
/* Deadline is in seconds*/
DWORD systime2sec(SYSTEMTIME *syst);
DWORD WINAPI compute_squares(LPVOID arg); 
/* Thread procedure method
 * WINAPI is __stdcall, a Windows API MACRO
 * for call convention.
 * LPVOID is a void long pointer for Windows API
 * and arg is the pointer data used for complex
 * and multiple parameters to the thread.*/
 
/*unsigned long int square_handleA1(unsigned long int n);*/


int check_parameters(int n_threads, int deadline, DWORD size){
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
		"parameter size.\n");
		return -1;
	}
	return 0;
}

/*unsigned long int square_handleA1(unsigned long int n){
	int i;
	int index;
	DWORD thread_id;
	if (!keep_running){
			return n;
	}
	
	thread_id = GetCurrentThreadId();
	index = -1;
	
	for (i=0; i < n_threads; i++){
			if (thread_id == threads_ids[i]){
					index = i;
					break;
			}
	}
	
	invocation_count[index]++;
	
	return square(n, 1);
}

unsigned long int square_handleA2(unsigned long int n){
	return n;
}
unsigned long int square_handleA3(unsigned long int n){
	return n;
}*/

DWORD systime2sec(SYSTEMTIME *syst){
		DWORD milli = 0;
		DWORD sec = 0;
		milli += syst -> wHour * 3600 * 1000;
		milli += syst -> wMinute * 60 * 1000;
		milli += syst -> wSecond * 1000;
		milli += syst -> wMilliseconds;
		sec = milli / 1000;
		return sec;
}

DWORD WINAPI compute_squares(LPVOID arg){
	DWORD size_n;
	DWORD i;
	int thread_id1;
	DWORD b_time, f_time, elapsed_time;
	int j, index;
	/*Size number and square call simulation*/
	SYSTEMTIME final_time;
	unsigned long int elapsed_time_lu;
	
	size_n = *(DWORD *)arg;
	
	for (i = 1 ; i <= size_n; i++){
		if (!keep_running){
				break;
		} else {
			square(i);	
		}
	}
	
	index = 0;
	thread_id1 = (int) GetCurrentThreadId();
	printf("+++++++++Thread id: %d\n", thread_id1);
	
	for (j=0; j<n_threads; j++){
			if (threads_ids[j] == thread_id1){
				index = j;
				break;
			}
	}
	
	GetSystemTime(&final_time);
	
	b_time = systime2sec(&begin_times[index]);
	f_time = systime2sec(&final_time);
	
	elapsed_time = f_time - b_time;
	elapsed_time_lu = elapsed_time;
	
	printf("%lu\n", elapsed_time_lu);
	printf("%d\n", invocation_count[index]);
	thread_finished++;
	
	return  0;	
}


int main (int argc, char *argv[]){
	DWORD size;
	int deadline;
	int k;
	if (argc != 4){
		printf("Error in procedure main: invalid parameter"
		" %d.\n", argc);
		return -1;
	}
	
	/*Convert strings to int*/
	n_threads = atoi(argv[1]);
	deadline = atoi(argv[2]);
	size = (DWORD)atoi(argv[3]);
	check_parameters(n_threads, deadline, size);
	
	/*Let's allocate memory for thread handles and parameters 
	 * for the windows program in two dinamically arrays (at runtime)
	 * (threads and they parameters)*/
	threads = malloc(n_threads * sizeof(HANDLE));
	/*HANDLE is a Windows datatype that represents a thread,
	 *  threads is a array of pointers of HANDLE objects.
	 * malloc performs dinamically allocation*/
	threads_ids = malloc(n_threads * sizeof(int));
	invocation_count = malloc(n_threads * sizeof(int));
	begin_times = malloc(n_threads * sizeof(SYSTEMTIME));
	
	if (threads == NULL || threads_ids == NULL ||
		invocation_count == NULL || begin_times == NULL){
		printf("Error in procedure main: invalid parameter"
		" %d.\n", n_threads);
		return -1;
	}
	
	/*Now, threads creation*/
	for (k = 0; k < n_threads; k++){
		invocation_count[k] = 0;
		GetSystemTime(&begin_times[k]);
		threads[k] = CreateThread(NULL, 6*1024*1024, compute_squares, 
			&size, 0, &imm_threadid);
		threads_ids[k] = imm_threadid;
		printf("Ids are: %d - %d\n", k, threads_ids[k]);
			/*Windows API function thread creation with:
			 * NULL for security alerts
			 * 0 default for stack size
			 * function name
			 * pointer to the parameter passed to the function,
			 * 		in this case size parameter
			 * 0 for flags, it will run immediately
			 * &threads_ids[i] a pointer to receive 
			 * 		the identifier*/
		if (threads[k] == NULL){
			printf("Error in procedure main: invalid parameter"
			" %d.\n", n_threads);
			return -1;
		}
	}
	
		
	Sleep(deadline * 1000); /*Function time is in miliseconds*/
	
	keep_running = FALSE;
	
	while (thread_finished < n_threads){
		Sleep(0.5);	
	}
	
	/*free(threads);
	free(threads_ids);
	free(invocation_count);
	free(begin_times);*/
	
	return 0;	
}
