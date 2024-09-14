/* NAME: Javier Andres Tarazona Jimenez, Nahian Sajid 
   NSID: elr490, Zas742
   Student Number: 11411898, 11309563

   CMPT 332 Term 1 2024

   Assignment 1

*/




 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

DWORD WINAPI compute_squares(LPVOID arg); /*DWORD in unsigned 32-bit integer*/
int square(int n);
void check_parameters(int n_threads, int n_squares, int deadline);

DWORD WINAPI compute_squares(LPVOID arg){
	
};

int square(int n){
	if (n < 0){
		printf("Error in square: invalid parameter n.\n" );
		return -1:
	}
	
	printf("Got to procedur square for n=%d.\n", n);
	return 0:
}

void check_parameters(int n_threads, int n_squares, int deadline){
	
};


int main (int argc, char *argv[]){
	return 0
	
}



