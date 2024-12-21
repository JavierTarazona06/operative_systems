/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210
   CMPT 332 Term 1 2024
   Assignment 1
*/

#include "kernel/types.h"
#include "user.h"

int
main(int argc, char *argv[]) {
	int mask;
	int proc_pid;
	
	if (argc < 3){
		printf("Send trace mask_num <program_calle> <if required_args>\n");
		exit(1);
	}
	
	mask = atoi(argv[1]);
	
      
    proc_pid = fork();
    if (proc_pid<0){
		fprintf(2, "Not forked\n");
		exit(1);
	}
	
	trace(mask);
    
    /*Call new function*/
    if (proc_pid == 0){
		/*printf("+++++++++It will be sent %s and %s\n", argv[2], argv[3]);*/
		exec(argv[2], &argv[2]);
		fprintf(2, "exec of trace failed\n"); 
		/*2 for xv6 standard error output*/
		exit(0);
	} else {
		wait(0);
	}    
    
    exit(0);
}
