#include <stdio.h>
#include <unistd.h>  // for gethostname
#include <limits.h>  // for HOST_NAME_MAX

int main() {

    char hostname[HOST_NAME_MAX];

    if (gethostname(hostname, (size_t) HOST_NAME_MAX) != 0) {
        perror("GETHOST");
        exit(EXIT_FAILURE);
    }
    printf("Machine Name: %s\n", hostname);
}