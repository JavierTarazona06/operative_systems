/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210
   CMPT 332 Term 1 2024
   Assignment 2
*/

typedef struct MessageSchat {
    char origin[256];
    char content[256];
    long seconds;
    long microseconds;
} MessageSchat;

/* ----- keyBoard_manager--------------- */

int nonblock_keyboard();
int read_keyboard(char *buffer_reading, int size_buffer);
int block_keyboard();

/* ----- udp_manager--------------- */

int configure_udp_sock_receive(int local_port, int *tosock_read);
int configure_udp_sock_send(int remote_port, const char* 
remote_host_name, int *tosock_send, struct sockaddr_in *tosend_addr);
int nonblock_udp(int sock_fd);
int udp_read(int sock_fd, MessageSchat *buffer_reading);
int udp_send(int sock_fd, MessageSchat *message, 
struct sockaddr_in send_addr);
int block_udp(int sock_fd);
char *GetHostName();
char *GetIP(char *hostName);
