#include "kernel/types.h"
#include "user.h"

int main() {
    if (symlink("target", "path") == 0) {
        printf("symlink system call succeeded\n");
    } else {
        printf("symlink system call failed\n");
    }
    exit(0);
}
