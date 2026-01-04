#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <linux/limits.h>

#include "builtin/cd.h"
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
        if (command == NULL)
            continue;

        if (strcmp(command, "exit") == 0) {
            break;
        }
        if (strcmp(command, "cd") == 0) {
            char *dir = strtok(NULL, " ");
            cd(dir);
            continue;
        }
        if (strcmp(command, "help") == 0) {
            printf("built-ins:\nexit version pwd cd\n");
            continue;
        }
        if (strcmp(command, "version") == 0) {
            printf("x9sh 0.0.0\n");
            continue;
        }
        if (strcmp(command, "pwd") == 0) {
            if (pwd(cwd, sizeof(cwd)) == 0) {
                printf("%s\n", cwd);
            }
            continue;
        }
        char *args[MAX_ARGS];
        int i = 0;
        while (command != NULL && i < MAX_ARGS - 1) {
            args[i++] = command;
            command = strtok(NULL, " ");
        }
        args[i] = NULL;
        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            perror("x9sh");
            exit(1);
        } else if (pid > 0) {
            wait(NULL);
        } else {
            perror("x9sh");
        }
    }

    return 0;
}
