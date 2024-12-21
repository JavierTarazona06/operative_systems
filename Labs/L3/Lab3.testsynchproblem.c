/* NAME: Javier Andres Tarazona Jimenez, Thomas Brown, Tianze Kuang, 
   NSID: elr490, vwg123, wde364
   Student Number: 11411898, 11332966, 11352826

   CMPT 332 Term 1 2024

   Lab 3
*/


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int compareoutfile(const char *outfile, const char *expecfile){
    char outline[300], expecline[300];
    FILE *out = fopen(outfile, "r");
    FILE *expected = fopen(expecfile, "r");
    

    if (!out || !expected){
        perror("Files not opened");
        return 0;
    }

    while (fgets(outline, sizeof(outline), out) && 
    fgets(expecline, sizeof(expecline), expected)){
        if (strcmp(outline, expecline) != 0){
            printf("Mismatch!!!!! Tast failed");
            fclose(out);
            fclose(expected);
            return 0;
        }
    }

    fclose(out);
    fclose(expected);

    return 1;
}

int main(int args, char *argv[]){
	int n, m;
	char expecfile[80];
	char *execu;
	char comm[300];
	int rest;
	int i;
	
	int tm = 5;
	int arr1[] = {5, 10, 10, 0, 25};
	int arr2[] = {15, 10, 7, 0, 100};
	
	/*if(args != 3){
		printf("Use: %s n m\n", argv[0]);
		return -1;
	}*/
	
	if(args != 1){
		printf("Use: %s\n", argv[0]);
		return -1;
	}
	
	execu = "./Lab3";
	/*n = atoi(argv[1]);
	m = atoi(argv[2]);*/
	
	for (i = 0; i<tm; i++){
		n = arr1[i];
		m = arr2[i];
	
		printf("Performing test %s %d %d...\n", execu, n, m);
		
		sprintf(expecfile, "testsout/lab3_testout%d_%d.txt", n, m);
		
		snprintf(comm, sizeof(comm), "./Lab3 %d %d > out_test.txt", n, m);

		rest = system(comm);
		if (rest != 0){
			printf("Error trying to run Lab3 :( \n");
			return 1;
		}
		
		rest = compareoutfile("out_test.txt", expecfile);
		
		assert(rest==1 && "The test Failed\n");
		printf("My test ./Lab3 %d %d has passed\n", n, m);
	}	

    return 0;
}
