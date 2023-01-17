#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE_LEN 256
int pid;

int main() {
    char command[MAX_LINE_LEN];

    while (1) {
        printf("mini_bash_>");
        fgets(command, MAX_LINE_LEN, stdin);

        // remove the newline character
        command[strcspn(command, "\n")] = 0;

        // exit if the command is "exit"
        if (strcmp(command, "exit") == 0) {
            break;
        }

        // create a child process

        char* argv[MAX_LINE_LEN];
        int argc = 0;

                    // parse the command into arguments
        char* token = strtok(command, " ");
        while (token != NULL) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL;

        if (strcmp(argv[0], "cd") == 0) {
            printf("%s\n", argv[1]);
            chdir(argv[1]);
        }

        pid = fork();

        if (pid == 0) {
            // the child process will execute the command

            // execute the command
            execvp(argv[0], argv);

            // if execvp returns, it means there was an error
            perror("execvp");
            exit(0);
        } else {
            // the parent process will wait for the child to finish
            wait(NULL);
        }
    }

    return 0;
}
