#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int execute_command(char *command, char **args) {
    pid_t pid;
    int status;

    /* TODO 1: Fork a child process */
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return -1;
    }

    /* TODO 2: Child process - Execute the command */
    if (pid == 0) {
        /* In child: replace process image with the requested command */
        execvp(command, args);

        /* If execvp returns, an error occurred */
        perror("execvp");
        exit(1); /* Must exit, do not return */
    }

    /* TODO 3: Parent process - Wait for child to complete */
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid failed");
        return -1;
    }

    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else {
        /* abnormal termination (e.g., killed by signal) */
        return -1;
    }
}
