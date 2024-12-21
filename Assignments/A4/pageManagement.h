/*
NAMEs: Javier Andres Tarazona Jimenez, Steven Baldwin
NSIDs: elr490, sjb956
Student Numbers: 11411898, 11300210
*/

void Memory_init(int numThreads);
int my_write(unsigned int virt_addr, int size, long int myId);
int my_read(unsigned int virt_addr, int size, long int myId);
