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

int nonblock_keyboard() {
    int flags_fd;
    printf("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB");

    flags_fd = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags_fd | O_NONBLOCK);

    return 0;
}

int read_keyboard(char *buffer_reading, int size) {
    ssize_t sz;
    int sz_count;

    sz_count = 0;
    while(1){
        sz = read(STDIN_FILENO, buffer_reading, size-1);
        printf("----------------sz es: %ld \n", sz);

        if (sz == -1){
            /*If it has not found an input...*/
            if (errno == EAGAIN || errno == EWOULDBLOCK){
                /*There is no available input*/
                buffer_reading[0] = '\0';
                printf("My A************************\n");
                /*return 0;*/
            } else {
                perror("read_keyboard");
                printf("My B ************************\n");
                return -1;
            }
        } else if (sz > 0){
            buffer_reading[sz] = '\0';
            printf("My C ************************\n");
            return 0;
        }
    }

    return 0;
}

int block_keyboard() {
    int flags_fd;
    printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");

    flags_fd = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags_fd & ~O_NONBLOCK);
    return 0;
}

int main(){
    char buffer[256];
    int temp;

    nonblock_keyboard();

    temp = read_keyboard(buffer, 256);
    printf("Result: %d\n", temp);
    printf("Str: %s\n", buffer);

    block_keyboard();

    return 0;
}