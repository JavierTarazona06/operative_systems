/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210
   CMPT 332 Term 1 2024
   Assignment 1
*/

#include "kernel/types.h"
#include "user.h"

int main(){
	/*Parent Process*/
	char buffer;
	int pipe1[2]; /*Parent-Child*/
	int pipe2[2]; /*Child-Parent*/
	pipe(pipe1);
	pipe(pipe2);
	int r1, r2;
	
	/*Child creation - if 0 it is the child process*/
	/*int pid = fork();*/
	
	if (fork()==0){
		/*Child*/
		close(pipe1[1]); /*C W*/
		close(pipe2[0]); /*C R*/
		
		r2 = read(pipe1[0], &buffer, 1);
		if (r2 == 1){
			printf("%d: received ping\n", getpid());
		}
		
		write(pipe2[1], &buffer, 1);
		
		close(pipe1[0]); /*Close read*/
		close(pipe2[1]); /*Close write*/
		
		exit(0);
		
	} else {
		/*Parent*/
		close(pipe1[0]); /*Close read*/
		close(pipe2[1]); /*Close write*/
		
		write(pipe1[1], &buffer, 1);
		
		r1 = read(pipe2[0], &buffer, 1);
		if (r1 == 1){
			printf("%d: received pong\n", getpid());
		}
		
		close(pipe1[1]);
		close(pipe2[0]);
		exit(0);
	}
	
}
