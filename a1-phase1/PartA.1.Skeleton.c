/*Namme: Javier Andres Tarazona Jimenez
 NSID: elr490
 Student Number: 11411898*/
 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

DWORD WINAPI compute_squares(LPVOID arg); 
/*DWORD is an unsigned 32-bit integer
 * WINAPI is __stdcall, a Windows API MACRO
 * for call convention.
 * LPVOID is a void long pointer for Windows API
 * and arg is the pointer data used for complex
 * and multiple parameters to the thread.*/

int square(int n);
void check_parameters(int n_threads, double deadline, int size);
/* Deadline is in seconds*/


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

DWORD WINAPI compute_squares(LPVOID arg){
	
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



int main (int argc, char *argv[]){
	return 0
	
}



