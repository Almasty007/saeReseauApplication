#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
pthread_mutex_t lock;
#define MAXLI 2048
char cmd[MAXLI];
char path[MAXLI];
char* commandeEntiere[MAXLI];
int pathidx;
int pid;
int nbargucmd;
void mbash();
void split();
void retirer_char_null();
void retirer_char_inv();
void afficherpwd();
void filsStockePwd();
void parentSetPwd();


int main(int argc, char** argv) {
  pthread_mutex_lock(&lock);
  while (1) {
    printf("Commande: ");
    fgets(cmd, MAXLI, stdin);
    pid = fork();
    mbash(cmd);
  }
  pthread_mutex_unlock(&lock);
  return 0;
}

void mbash() {
  if(pid == 0){
      printf("Execute: %s", cmd);
      printf("argument cmd %%s --> %s \n", cmd);

      //exit
      if(strncmp(cmd, "exit", 4) == 0) {
      //tue le parent
        pthread_mutex_unlock(&lock);
        kill(getppid(), 15);
      }
      //essaye le pwd
      if(strncmp(cmd, "pwd", 3) == 0){
        afficherpwd();
      }
    exit(0);
    } else {
    //essaye le cd
    if(strncmp(cmd, "cd", 2) == 0) {
    split();
      if(nbargucmd == 2){
          retirer_char_inv(commandeEntiere[1]);
          if(chdir(commandeEntiere[1]) != 0){
              printf("Erreur lors du chargement du chemin \n");
          }
      } else {
      printf("%d arg \n", nbargucmd);
      }
    }
     int status = 0;
     //printf("je suis le pere (%d) et j'attend la mort de mon enfant \n", getpid()) ;
     wait(&status);
     //printf("Le fils est mort avec le statut %d\n", status);
  }
}

void split() {
    char *tmp;
    int i = 0;
    tmp = strtok(cmd, " ");
    while(tmp != NULL) {
        commandeEntiere[i] = tmp;
        tmp = strtok(NULL, " ");
        i++;
    }
    nbargucmd = i;
}

void retirer_char_null(char* chaine){
    int len = strlen(chaine);
    for(int i = 0; i < len; i++){
        if(chaine[i] == '\0'){
            for(int j = i; j < len-1; j++){
                chaine[j] = chaine[j+1];
            }
            chaine[len-1] = '\0';
            break;
        }
    }
}

void retirer_char_inv(char* chaine){
    int len = strcspn(chaine, " \t\n\r\v\f");
    chaine[len] = '\0';
}

void afficherpwd(){
    char path[MAXLI];
    if(getcwd(path, sizeof(path)) != NULL){
        printf("chemin actuel : %s \n", path);
    } else {
        printf("erreur lors de la recherche du chemin actuel");
    }
}






