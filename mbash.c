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
void mbash();
void split();


int main(int argc, char** argv) {
  pthread_mutex_lock(&lock);
  while (1) {
    printf("Commande: ");
    fgets(cmd, MAXLI, stdin);
    pid = fork();
    mbash(cmd);
    //split();
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
      //tue le pid du parent
        pthread_mutex_unlock(&lock);
        kill(getppid(), 15);
        exit(0);

      }
      //if()

//      else {
//        system(cmd);
//      }
  }
  else {
     int status = 0;
     printf("je suis le pere (%d) et j'attend la mort de mon enfant \n", getpid()) ;
     wait(&status);
     printf("Le fils est mort avec le statut %d\n", status);
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
}