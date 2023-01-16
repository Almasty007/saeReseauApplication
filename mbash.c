#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 256

int main() {
    char input[MAX_LINE_LENGTH];

    while (1) {
        // Afficher le prompt
        printf("mbash> ");
        fgets(input, MAX_LINE_LENGTH, stdin);

        // Retirer le caractère de nouvelle ligne de la fin de la chaîne
        input[strcspn(input, "\n")] = 0;

        // Séparer la commande et ses arguments
        char *args[MAX_LINE_LENGTH];
        char *token = strtok(input, " ");
        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (strcmp(args[0], "cd") == 0) {
            // Exécuter la commande cd
            chdir(args[1]);
        } else if (strcmp(args[0], "pwd") == 0) {
            // Exécuter la commande pwd
            char cwd[MAX_LINE_LENGTH];
            getcwd(cwd, sizeof(cwd));
            printf("%s\n", cwd);
        } else {
            // Exécuter la commande via execve
            pid_t pid = fork();
            if (pid == 0) {
                // Exécuter la commande dans le processus fils
                execve(args[0], args, NULL);
                exit(0);
            } else if (args[i-1] != "&") {
                // Attendre la fin de l'exécution de la commande dans le processus père si le & n'est pas présent
                wait(NULL);
            }
        }
    }
    return 0;
}