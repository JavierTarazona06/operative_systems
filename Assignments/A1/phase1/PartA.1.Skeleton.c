/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
   NSID: elr490, sjb956
   Student Number: 11411898, 

   CMPT 332 Term 1 2024

   Assignment 1

*/

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

int check_parameters(int n_threads, int deadline, DWORD size);
/* Deadline is in seconds*/
int square(int n);
DWORD WINAPI compute_squares(LPVOID arg); 
/* Thread procedure method
 * WINAPI is __stdcall, a Windows API MACRO
 * for call convention.
 * LPVOID is a void long pointer for Windows API
 * and arg is the pointer data used for complex
 * and multiple parameters to the thread.*/


int check_parameters(int n_threads, int deadline, DWORD size){
	if (n_threads < 1){
		printf("Error in procedure check_parameters: invalid "
		"parameter %d.\n", n_threads);
		return -1;
	}
	if (deadline < 0) {
		printf("Error in procedure check_parameters: invalid "
		"parameter %d.\n", deadline);
		return -1;
	}
	if (size < 1){
		printf("Error in procedure check_parameters: invalid "
		"parameter %d.\n", size);
		return -1;
	}
	printf("Got to procedure check_parameters\n");
	return 0;
}

int square(int n){
	if (n < 0){
		printf("Error in procedure square: invalid parameter %d.\n", n);
		return -1;
	} else {
		printf("Got to procedure square\n");
		return 0;
	}	
}

DWORD WINAPI compute_squares(LPVOID arg){
	DWORD size_n;
	DWORD i;
	/*Size number and square call simulation*/
	printf("Got to procedure compute_squares\n");
	size_n = *(DWORD *)arg;
	
	for (i = 1 ; i <= size_n; i++){
		square(i);
	}
	
	return  0;	
}


int main (int argc, char *argv[]){
	DWORD size;
	int deadline;
	int k;
	int l;
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
	threads_ids = malloc(n_threads * sizeof(DWORD));
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
		threads[k] = CreateThread(NULL, 0, compute_squares, 
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
	
	keep_running = FALSE;
	
	/*Threads to finish, before cleaning up*/
	for (l = 0; l < n_threads; l++){
			WaitForSingleObject(threads[l], INFINITE);
			CloseHandle(threads[l]);
	}
	
	free(threads);
	free(threads_ids);
	free(invocation_count);
	free(begin_times);
	
	return 0;	
}
