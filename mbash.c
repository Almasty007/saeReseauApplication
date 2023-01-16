#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <signal.h>
#define MAXLI 2048
char cmd[MAXLI];
char path[MAXLI];
int pathidx;
void mbash();
int pid;


int main(int argc, char** argv) {
  while (1) {
    printf("Commande: ");
    fgets(cmd, MAXLI, stdin);
    pid = fork();
    mbash(cmd);
  }
  return 0;
}

void mbash() {
  printf("Execute: %s", cmd);
  printf("print cmd %%d --> %d \n", *cmd);
  printf("print cmd %%s --> %s \n", cmd);

  //exit
  if(strcmp(cmd, "exit") && pid==0) {
  //tue le pid du parent
    kill(getppid(), 15);
//    printf("try exit \n");
//    char* killdetail[2048] =  {"kill"};
//    char* ch = (char*)malloc(2048*sizeof(char));
//    sprintf(ch, "%d", pid);
//    printf("pid --> %d", pid);
//    printf("print killdetail --> %s ; %s \n", killdetail[0], ch);
//
//    execve("/bin/kill", killdetail, NULL);
  } else {
    system(cmd);
  }

  //test

}