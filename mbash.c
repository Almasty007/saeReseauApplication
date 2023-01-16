#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <signal.h>
#define MAXLI 2048
char cmd[MAXLI];
char path[MAXLI];
char* commandeEntiere[MAXLI];
int pathidx;
int pid;
void mbash();
void split();


int main(int argc, char** argv) {
  while (1) {
    printf("Commande: ");
    fgets(cmd, MAXLI, stdin);
    pid = fork();
    mbash(cmd);
    //split();
  }
  return 0;
}

void mbash() {
  if(pid == 0){
      printf("Execute: %s", cmd);
      printf("print cmd %%d --> %d \n", *cmd);
      printf("print cmd %%s --> %s \n", cmd);
      printf("test %d \n", strncmp(cmd, "exit", 4));

      //exit
      if(strncmp(cmd, "exit", 4) == 0) {
      //tue le pid du parent
        kill(getppid(), 15);

      }
      //if()

      else {
        system(cmd);
      }
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