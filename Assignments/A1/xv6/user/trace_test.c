/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210
   CMPT 332 Term 1 2024
   Assignment 1
*/

#include "kernel/types.h"
#include "user.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"

int
main(int args, char *argv[]){
	/*const char *syscallArray[23];
	syscallArray[1] = "fork";
	syscallArray[2] = "exit";
	syscallArray[3] = "wait";
	syscallArray[4] = "pipe";
	syscallArray[5] = "read";
	syscallArray[6] = "kill";
	syscallArray[7] = "exec";
	syscallArray[8] = "fstat";
	syscallArray[9] = "chdir";
	syscallArray[10] = "dup";
	syscallArray[11] = "getpid";
	syscallArray[12] = "sbrk";
	syscallArray[13] = "sleep";
	syscallArray[14] = "uptime";
	syscallArray[15] = "open";
	syscallArray[16] = "write";
	syscallArray[17] = "mknod";
	syscallArray[18] = "unlink";
	syscallArray[19] = "link";
	syscallArray[20] = "mkdir";
	syscallArray[21] = "close";
	syscallArray[22] = "trace";*/
	
	int test_number;
	int times = 1;
	char *args_0[1];
	int p[2];
	int i;
	char buf[100], buf1[12];
	struct stat st;
	int fd = -1;
	/*printf("----------Args is: %d\n", args);*/
	
	if (args < 2){
		printf("It must be send trace_test test_numer times_optional\n");
		exit(1);
	}
	
	test_number = atoi(argv[1]);
	
	if (args == 3){
		times = atoi(argv[2]);
	}	
	
	if (test_number < 0 || test_number > 21){
		printf("Test Unavailable\n");
		exit(1);
	} else if (test_number == 0){
		/*Call new function*/
		printf("Pingpong Program Traced\n");
		if (fork() == 0){
			args_0[0] = 0;
			exec("./pingpong", args_0);
			fprintf(2, "exec of trace failed\n"); 
			/*2 for xv6 standard error output*/
			exit(0);
		} else {
			wait(0);
		}
	} else{
		/*printf("%s tests:\n", syscallArray[test_number]);*/
		i=0;
		
		if (test_number == 1){
			for (i=0; i<times; i++){
				fork();
			}
		} else if (test_number == 2){
			for (i=0; i<times; i++){
				exit(0);
			}
		} else if (test_number == 3){
			for (i=0; i<times; i++){
				wait(0);
			}
		} else if (test_number == 4){
			for (i=0; i<times; i++){
				pipe(p);
			}
		} else if (test_number == 5){
			fd = open("testfile.txt", 0);
			for (i=0; i<times; i++){
				read(fd, buf, sizeof(buf));
			}
			close(fd);
		} else if (test_number == 6){
			for (i=0; i<times; i++){
				kill(1);
			}
		} else if (test_number == 7){
			for (i=0; i<times; i++){
				printf("Execute test 0 to view exec performance.\n");
			}
		} else if (test_number == 8){
			for (i=0; i<times; i++){
				fstat(1, &st);
			}
		} else if (test_number == 9){
			for (i=0; i<times; i++){
				chdir("/");
			}
		} else if (test_number == 10){
			for (i=0; i<times; i++){
				dup(1);
			}
		} else if (test_number == 11){
			for (i=0; i<times; i++){
				getpid();
			}
		} else if (test_number == 12){
			for (i=0; i<times; i++){
				sbrk(4096);
			}
		} else if (test_number == 13){
			for (i=0; i<times; i++){
				sleep(1);
			}
		} else if (test_number == 14){
			for (i=0; i<times; i++){
				uptime();
			}
		} else if (test_number == 15){
			for (i=0; i<times; i++){
				open("testfile.txt", 0);
			}
		} else if (test_number == 16){
			for (i=0; i<times; i++){
				fd = open("testfile.txt", 1);
				strcpy(buf1, "Hello");
				write(fd, buf, sizeof(buf1));
			}
			close(fd);
		} else if (test_number == 17){
			for (i=0; i<times; i++){
				mknod("testfile", 1, 1);
			}
		} else if (test_number == 18){
			for (i=0; i<times; i++){
				mknod("testfile", 1, 1);
				unlink("testfile");
			}
		} else if (test_number == 19){
			for (i=0; i<times; i++){
				link("testfile", "linkfile");
			}
		} else if (test_number == 20){
			for (i=0; i<times; i++){
				mkdir("testdir");
			}
		} else if (test_number == 21){
			for (i=0; i<times; i++){
				fd = open("testfile.txt", O_RDONLY);
				close(fd);
			}
		} else if (test_number == 22){
			printf("22 is command Trace");
		}		
	}
	
	exit(0);
	
}
