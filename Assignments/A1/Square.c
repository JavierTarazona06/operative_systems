/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 1

*/

#include <partA.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__MINGW32__) || defined(_WIN32)
	#include <windows.h>
#elif defined(__linux__)
	#include <sys/types.h>
	#include <sys/time.h>
	#include <unistd.h>
	#include <standards.h>
	#include <os.h>
	#include <pthread.h>
#else
	#include <windows.h>
#endif

unsigned long int square(unsigned long int n);

#if defined(__MINGW32__) || defined(_WIN32)
	unsigned long int square(unsigned long int n){
		DWORD cur_thread_id;
		int index, j;
		
		if (!keep_running){
			return n;
		} else {
			cur_thread_id = GetCurrentThreadId();
			for (j=0; j<n_threads; j++){
					if (threads_ids[j] == cur_thread_id){
						index = j;
						break;
					}
			}
			invocation_count[index]++;
			if (n==0){
				return 0;
			} else {
				return square(n-1) + n + n - 1;
			}
		}
		return 0;
	}
#elif defined(__linux__)
	unsigned long int square(unsigned long int n){
		int i;
		int index;
		int thread_id;
		pthread_t pthread_id;
		
		if (part == 2){
			thread_id = (int) MyPid();
			index = -1;
			
			for (i=0; i < n_threads; i++){
					if (thread_id == threads_ids_int[i]){
							index = i;
							break;
					}
			}
			
			invocation_count[index]++;
			
			if (n==0){
				return 0;
			} else {
				return square(n-1) + n + n - 1;
			}	
		} else if (part == 3){
			if (!keep_running){
				return n;
			} else {
				pthread_id = pthread_self();
				index = -1;
				
				for (i=0; i < n_threads; i++){
						if (pthread_equal(pthread_id, threads[i])){
								index = i;
								break;
						}
				}
				
				invocation_count[index]++;
				
				if (n==0){
					return 0;
				} else {
					return square(n-1) + n + n - 1;
				}
			}
		}
		return 0;
	}
#else
	unsigned long int square(unsigned long int n){
		if (part==1){
			DWORD cur_thread_id;
			int index, j;
			
			if (!keep_running){
				return n;
			} else {
				cur_thread_id = GetCurrentThreadId();
				for (j=0; j<n_threads; j++){
						if (threads_ids[j] == cur_thread_id){
							index = j;
							break;
						}
				}
				invocation_count[index]++;
				if (n==0){
					return 0;
				} else {
					return square(n-1) + n + n - 1;
				}
			}
		}
		return 0;
	}
#endif
