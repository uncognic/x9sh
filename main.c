#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <errno.h>
#include <limits.h>
#include "builtin/pwd.h"

#define MAX_ARGS 64

int main() {
    char input[MAX_INPUT];

    while (1) {
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s > ", cwd);
        }
        if (!fgets(input, sizeof(input), stdin))
            break;

        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0)
            continue;

        char *command = strtok(input, " ");
        char *arg = strtok(nullptr, " ");

        if (strcmp(input, "exit") == 0)
            break;
        if (strcmp(input, "help") == 0)
            printf("HELP\n");
        if (strcmp(input, "version") == 0)
            printf("VERSION\n");
        if (strcmp(input, "cd") == 0)
            printf("CD\n");
        if (strcmp(input, "pwd") == 0)
            if (pwd(cwd, sizeof(cwd)) == 0) {
                printf("\n%s\n", cwd);
            }

        char *args[MAX_ARGS];
        int i = 0;
        char *token = strtok(input, " ");
        while (token != nullptr && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(nullptr, " ");
        }
        args[i] = nullptr;
        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            perror("x9sh");
            exit(1);
        } else if (pid > 0) {
            wait(nullptr);
        } else {
            perror("x9sh");
        }
    }

    return 0;
}
