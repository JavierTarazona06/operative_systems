/*Namme: Javier Andres Tarazona Jimenez
 NSID: elr490
 Student Number: 11411898*/
 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

volatile BOOL keep_running = TRUE;
int *invocation_count;
HANDLE *threads;
DWORD *threads_ids;
/* DWORD is an unsigned 32-bit integer*/
SYSTEMTIME *begin_times;
int n_threads;

void check_parameters(int n_threads, double deadline, int size);
/* Deadline is in seconds*/
int square(int n);
DWORD WINAPI compute_squares(LPVOID arg); 
/* Thread procedure method
 * WINAPI is __stdcall, a Windows API MACRO
 * for call convention.
 * LPVOID is a void long pointer for Windows API
 * and arg is the pointer data used for complex
 * and multiple parameters to the thread.*/


void check_parameters(int n_threads, double deadline, int size){
	if (n_threads < 1){
		printf("Error in procedure check_parameters: invalid "
		"parameter %d.\n", n_threads);
		return -1:
	}
	if (deadline < 0) {
		printf("Error in procedure check_parameters: invalid "
		"parameter %lf.\n", deadline);
		return -1:
	}
	if (size < 1){
		printf("Error in procedure check_parameters: invalid "
		"parameter %d.\n", size);
		return -1;
	}
	printf("Got to procedure check_parameters\n");
	return 0;
};

int square(int n){
	if (n < 0){
		printf("Error in procedure square: invalid parameter %d.\n", n);
		return -1:
	} else {
		printf("Got to procedure square\n");
		return 0:
	}	
}

DWORD WINAPI compute_squares(LPVOID arg){
	/*Size number and square call simulation*/
	printf("Got to procedure compute_squares\n");
	int size = *(int *)arg;
	
	for (int i = 1; i <= size; i++){
		square(i);
	}
	
	return  0;	
}


int main (int argc, char *argv[]){
	if (argc != 4){
		printf("Error in procedure main: invalid parameter"
		" %d.\n", argc);
		return -1:
	}
	
	/*Convert strings to int*/
	int n_threads = atoi(argv[1]);
	int deadline = atoi(argv[2]);
	int size = atoi(argv[3]);
	check_parameters(n_threads, deadline, size);
	
	/*Let's allocate memory for thread handles and parameters 
	 * for the windows program in two dinamically arrays (at runtime)
	 * (threads and they parameters)*/
	threads = malloc(n_threads * sizeof(HANDLE));
	/*HANDLE is a Windows datatype that represents a thread,
	 *  threads is a array of pointers of HANDLE objects.
	 * malloc performs dinamically allocation*/
	thread_ids = malloc(n_threads * sizeof(DWORD));
	invocation_count = malloc(n_threads * sizeof(int));
	begin_times = malloc(n_threads * sizeof(DWORD));
	
	if (threads == NULL || thread_ids == NULL ||
		invocation_count == NULL || begin_times == NULL){
		printf("Error in procedure main: invalid parameter"
		" %d.\n", n_threads);
		return -1:
	}
	
	/*Now, threads creation*/
	for (int i = 0; i < n_threads; i++){
		invocation_count[i] = 0;
		GetSystemTime(&begin_times[i])
		threads[i] CreateThread(NULL, 0, compute_squares, 
			&size, 0, &threads_ids[i]);
			/*Windows API function thread creation with:
			 * NULL for security alerts
			 * 0 default for stack size
			 * function name
			 * pointer to the parameter passed to the function,
			 * 		in this case size parameter
			 * 0 for flags, it will run immediately
			 * &threads_ids[i] a pointer to receive 
			 * 		the identifier*/
			printf("Created aaaa")
		if (threads[i] == NULL){
			printf("Error in procedure main: invalid parameter"
			" %d.\n", n_threads);
			return -1:
		}
	}
	
	Sleep(deadline * 1000); /*Function time is in miliseconds*/
	
	keep_running = FALSE;
	
	/*Threads to finish, begor cleaning up*/
	for (int i = 0; i < n_threads, i++){
			WaitForSingleObject(threads[i], INFINITE);
			CloseHandle(threads[i]);
	}
	
	free(threads);
	free(thread_ids);
	free(invocation_count);
	free(begin_times);
	
	return 0	
}



