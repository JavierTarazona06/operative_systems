/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210
   CMPT 332 Term 1 2024
   Assignment 1
*/

/* ----- keyBoard_manager--------------- */

int nonblock_keyboard();
int read_keyboard(char *buffer_reading);
int block_keyboard();

/* ----- udp_manager--------------- */

int bind_udp_sock(int port);
int nonblock_udp(int sock_fd);
char *udp_read(int sock_fd);
int block_udp(int sock_fd);
