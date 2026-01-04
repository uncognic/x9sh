#include "pwd.h"
#include <stdio.h>
#include <unistd.h>

int pwd(char *buffer, size_t size) {
    if (getcwd(buffer, size) != NULL) {
        return 0;
    } else {
        perror("getcwd failed");
        return -1;
    }
}