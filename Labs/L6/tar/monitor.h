/*#NAME: Javier Andres Tarazona Jimenez
#NSID: elr490
#Student Number: 11411898

#CMPT 332 Term 1 2024

#Lab 4*/

#include "list.h"

void *Get_Item(LIST* big_list, int index);
void RttMonInit(int numConds);
void RttMonEnter(void);
void RttMonLeave(void);
void RttMonWait(int cv);
void RttMonSignal(int cv);