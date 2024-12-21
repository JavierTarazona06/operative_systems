/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 1

*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <partA.h>

HANDLE *threads;
DWORD *threads_ids;
unsigned long int *invocation_count;
/* DWORD is an unsigned 32-bit integer*/
SYSTEMTIME *begin_times;

int keep_running = 1;
int n_threads;
int thread_finished = 0;
int part;

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
	DWORD cur_thread_id;
	int index, j;
	unsigned int i;
	SYSTEMTIME final_time;
	DWORD b_time, f_time, elapsed_time;
	unsigned long int elapsed_time_lu;
	
	size_n = *(DWORD *)arg;
	
	for (i = 1 ; i <= size_n; i++){
		if (!keep_running){
				break;
		} else {
			square(i);
		}
	}
	
	cur_thread_id = GetCurrentThreadId();
	for (j=0; j<n_threads; j++){
			if (threads_ids[j] == cur_thread_id){
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
	printf("%lu\n", invocation_count[index]);
	
	
	thread_finished++;
	return 0;
}


int main (int argc, char *argv[]){
	DWORD size;
	int deadline;
	int k;
	
	part = 1;
	
	if (argc != 4){
		printf("Error in procedure main: invalid parameter"
		" %d.\n", argc);
		return -1;
	}
	
	/*Convert strings to int*/
	n_threads = atoi(argv[1]);
	deadline = atoi(argv[2]);
	size = (DWORD)atoi(argv[3]);
	if (check_parameters(n_threads, deadline, size) != 0){
		return -1;
	}
	
	/*Let's allocate memory for thread handles and parameters 
	 * for the windows program in two dinamically arrays (at runtime)
	 * (threads and they parameters)*/
	threads = malloc(n_threads * sizeof(HANDLE));
	/*HANDLE is a Windows datatype that represents a thread,
	 *  threads is a array of pointers of HANDLE objects.
	 * malloc performs dinamically allocation*/
	threads_ids = malloc(n_threads * sizeof(DWORD));
	invocation_count = malloc(n_threads * sizeof(unsigned long int));
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
			&size, 0, &threads_ids[k]);
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
	
	keep_running = 0;
	
	while (thread_finished < n_threads){
		Sleep(0.5);	
	}
	
	return 0;	
}
