#ifndef MONITOR_HEADER
#define MONITOR_HEADER

void MonInit(int);
void MonEnter();
void MonLeave();
void MonWait(int);
void MonSignal(int);

#endif