/*Namme: Javier Andres Tarazona Jimenez
 NSID: elr490
 Student Number: 11411898*/
 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void check_parameters(int n_threads, double deadline, int size);
/* Deadline is in seconds*/
int square(int n);
DWORD WINAPI compute_squares(LPVOID arg); 
/* Thread procedure method
 * DWORD is an unsigned 32-bit integer
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
		printf("Error in procedure square: invalid parameter n.\n" );
		return -1:
	} else {
		printf("Got to procedure square\n");
		return 0:
	}	
}

DWORD WINAPI compute_squares(LPVOID arg){
	/*Thread number and square call simulation*/
	printf("Got to procedure compute_squares\n");
	int thread_number = *(int *)arg;
	for (int i = 1; i <= 200; i++){
		square(i);
	}
	return  0;	
}


int main (int argc, char *argv[]){
	return 0
	
}



