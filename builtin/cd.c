#include "cd.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/limits.h>

char lastdir[PATH_MAX];

int cd(char *arg) {
    char curdir[PATH_MAX];
    if (!getcwd(curdir, sizeof(curdir))) {
        perror("getcwd");
        return 1;
    }
    if (arg == NULL) {
        arg = getenv("HOME");
    }
    if  (!strcmp(arg, "-")) {
        if (*lastdir == '\0') {
            fprintf(stderr, "cd: no directory specified\n");
            return 1;
        } else {
            arg = lastdir;;
        }
    }
    if (chdir(arg) != 0) {
        fprintf(stderr, "cd: %s: %s\n", arg, strerror(errno));
        return 1;
    }
    strcpy(lastdir, curdir);
    return 0;
}