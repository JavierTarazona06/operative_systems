/*NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
 *NSID: elr490, sjb956
 *Student Number: 11411898, 11300210
*/

#ifndef MONITOR_HEADER
#define MONITOR_HEADER

void MonInit(int);
void MonEnter();
void MonLeave();
void MonWait(int);
void MonSignal(int);

#endif
