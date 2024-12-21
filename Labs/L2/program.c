/* CMPT 332 Fall 2023
* Lab 2 - sample program
* Originally by Kai Langen, 2018
* Updated by Delaney Sander, 2023
* NSID: protected
* Student Number: protected
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	int i, x, y, arrSize, *iPtr1, *iPtr2;
	int *numbers, *heapNeighbour;
	int mallocBlk;
	arrSize = 50;

	/*
	* Initialize arrays with numbers.
	*/

	numbers = malloc(sizeof(int) * arrSize);
	heapNeighbour = malloc(sizeof(int) * (arrSize/2));	
	mallocBlk = heapNeighbour[-2];
	
	numbers[0]  = 0;
	heapNeighbour[0] = 1;
	for(i = 1; i < arrSize; i++) {
		numbers[i] = i+numbers[i-1]+1;
		if (i < arrSize/2)
			heapNeighbour[i] = heapNeighbour[i-1]*2;
	}

	/*
	* Weird for-loop with lots of effects
	*/
	for(i = 0; i < arrSize; i++) {
		x = numbers[i];
		iPtr1 = &numbers[x % arrSize];
		y = (*iPtr1) * 2;
		iPtr2 = &numbers[(y % arrSize)+20];
		*iPtr2 = x;
	}

	free(numbers);

	/* restore malloc info */
	heapNeighbour[-2] = mallocBlk;
	free(heapNeighbour);

	return 0;
}
