#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAXLI 2048
int pid;

int main() {
    char cmd[MAXLI];

    // la boucle principale

    while (1) {

        printf("mini_bash_>");

        // recuperation de la commande de l'utilisateur
        fgets(cmd, MAXLI, stdin);
        cmd[strcspn(cmd, "\n")] = 0;

        // la fonction d'arret si la commande vaut exit
        if (strcmp(cmd, "exit") == 0) {
            break;
        }

        // la separation de la commande pour la recuperation des attributs
        char* argv[MAXLI];
        int argc = 0;

        char* tempo = strtok(cmd, " ");
        while (tempo != NULL) {
            argv[argc++] = tempo;
            tempo = strtok(NULL, " ");
        }
        argv[argc] = NULL;

        // le changement de repertoire

        if (strcmp(argv[0], "cd") == 0) {
            chdir(argv[1]);
        }else{

        // creation de fils pour exectution des autres commandes

        pid = fork();


        if (pid == 0) {
            char* fullpath = (char *) malloc(MAXLI);
            sprintf(fullpath,"/bin/%s",argv[0]);
            if(execve(fullpath, argv, NULL) != 0) {
                perror("execvp");
            };
            free(fullpath);
            exit(0);
        } else {
            wait(NULL);
        }
    }
    }

    return 0;
}
