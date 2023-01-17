#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_LINE_LEN 256
int pid = 1;
int pid = 1;

int main() {
    char cmd[MAX_LINE_LEN];

    while (1) {
        printf("mini_bash_>");
        fgets(cmd, MAX_LINE_LEN, stdin);

        // remove the newline character
        cmd[strcspn(cmd, "\n")] = 0;

        // exit if the cmd is "exit"
        if (strcmp(cmd, "exit") == 0) {
            break;
        }

        // create a child process

        char* argv[MAX_LINE_LEN];
        int argc = 0;

                    // parse the cmd into arguments
        char* token = strtok(cmd, " ");
        while (token != NULL) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL;

        if (strcmp(argv[0], "cd") == 0) {
            chdir(argv[1]);
        }else{

        pid = fork();
        }

        if (pid == 0) {
            execve("/bin/"+argv[0], argv);
            perror("execvp");
            exit(0);
        } else {
            wait(NULL);
        }
    }
    return 0;
}
