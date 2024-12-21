/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 1

*/

#ifndef PARTA_H
	#define PARTA_H

	#if defined(__MINGW32__) || defined(_WIN32)
		#include <windows.h>
		/*A1*/
		extern DWORD *threads_ids;
		extern int part;
		
		extern int keep_running;
		
		extern unsigned long int *invocation_count;

		extern int n_threads;

		extern unsigned long int square(unsigned long int n);
		
	#elif defined(__linux__)
		#include <pthread.h>
		extern pthread_t *threads;
		extern int *threads_ids_int;
		extern int part;
		
		extern int keep_running;
	
		extern unsigned long int *invocation_count;

		extern int n_threads;

		extern unsigned long int square(unsigned long int n);
	
	#else
		#include <windows.h>
		/*A1*/
		extern DWORD *threads_ids;
		extern int part;
		
		extern int keep_running;
		
		extern unsigned long int *invocation_count;

		extern int n_threads;

		extern unsigned long int square(unsigned long int n);
	#endif
#endif
