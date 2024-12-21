/* NAME: Javier Andres Tarazona Jimenez, Steven Baldwin 
   NSID: elr490, sjb956
   Student Number: 11411898, 11300210

   CMPT 332 Term 1 2024

   Assignment 2
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

# include <rtthreads.h>

#include <s-chat.h>

int nonblock_keyboard() {
    int flags_fd;

    flags_fd = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags_fd | O_NONBLOCK);

    return 0;
}

int read_keyboard(char *buffer_reading, int size_buffer) {
    ssize_t sz;

    while(1){
        sz = read(STDIN_FILENO, buffer_reading, size_buffer-1);

        if (sz == -1){
			/*If it has not found an input...*/
            if (errno == EAGAIN || errno == EWOULDBLOCK){
				/*There is no available input*/
                buffer_reading[0] = '\0';
                return 0;
            } else {
                perror("read_keyboard");
                return -1;
            }
        } else if (sz > 0){
            buffer_reading[sz] = '\0';
            return 0;
        }
    }
    
    return 0;
}

int block_keyboard() {
    int flags_fd;

    flags_fd = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags_fd & ~O_NONBLOCK);
    return 0;
}
