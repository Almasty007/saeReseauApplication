#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE_LEN 256

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
        pid_t pid = fork();
        if (pid == 0) {
            // the child process will execute the command
            char* argv[MAX_LINE_LEN];
            int argc = 0;

            // parse the command into arguments
            char* token = strtok(command, " ");
            while (token != NULL) {
                argv[argc++] = token;
                token = strtok(NULL, " ");
            }
            argv[argc] = NULL;

            // execute the command
            execvp(argv[0], argv);

            // if execvp returns, it means there was an error
            perror("execvp");
            exit(1);
        } else {
            printf("%s\n", command);
            if (strcmp(command, "cd") == 0) {
                break;
            }
            // the parent process will wait for the child to finish
            wait(NULL);
        }
    }

    return 0;
}
