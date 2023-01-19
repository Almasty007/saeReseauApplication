#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <ncurses.h>

#define MAXLI 2048
int pid;
void lireFichier();

int main() {
    char cmd[MAXLI];

    // la boucle principale

    while (1) {

        printf("minibash>");

        // recuperation de la commande de l'utilisateur
        if(fgets(cmd, MAXLI, stdin) == NULL){
            break;
        }

        // on retire le dernier charactere qui est insisible
        cmd[strcspn(cmd, "\n")] = 0;
        
        //si la chaine est vide, on skip la boucle
        //a faire

        // la fonction d'arret si la commande vaut exit
        if (strcmp(cmd, "exit") == 0) {
            break;
        }

        // la separation de la commande pour la recuperation des attributs
        char* argv[MAXLI];
        int argc = 0;

        //on split par " " --> espace vide
        char* tempo = strtok(cmd, " ");
        while (tempo != NULL) {
            argv[argc++] = tempo;
            tempo = strtok(NULL, " ");
        }
        argv[argc] = NULL;

        //nettoye le terminal
        if (strcmp(argv[0], "clear") == 0) {
            //a faire
            initscr();
            endwin();
        }else if (strcmp(argv[0], "cd") == 0) {

        // le changement de repertoire
            chdir(argv[1]);
        }else{


        // creation de fils pour execution des autres commandes
        pid = fork();


        if (pid == 0) {
            if(strcmp(argv[0], "history") == 0){
                printf("historique \n");
                lireFichier();
            } else {
                char* fullpath = (char *) malloc(MAXLI);
                sprintf(fullpath,"/bin/%s",argv[0]);
                if(execve(fullpath, argv, NULL) != 0) {
                    perror("execvp");
                }
                free(fullpath);
            }
            exit(0);
        } else {
            wait(NULL);
        }
        }
    }

    return 0;
}

void lireFichier(){
    FILE* fp;
    char c;

    //on declare la variable avec l'allocation de variables
    char* pathfichier = (char *) malloc(MAXLI);
    //on recupere le username de l'utilisateur
    char* username = getlogin();

    //on concatene les deux chaines
    sprintf(pathfichier,"/home/%s",username);

    //on change le repertoire courrant du processus
    chdir(pathfichier);

    //on libere la memoire allouee
    free(pathfichier);

    // on ouvre le fichier en mode lecture uniquement
    fp = fopen(".bash_history", "r");

    // on verifie si le fichier peut etre ouvert
    if (fp == NULL) {
        printf("le fichier ne peut pas etre ouvrir\n");
    }

    // on affiche le contenu char par char jusqu'a EOF
    while ((c = fgetc(fp)) != EOF) {
        printf("%c", c);
    }

    // on ferme le fichier
    fclose(fp);
}