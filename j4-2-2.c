#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main(int argc, char **argv){

  int pid, w, i;
  char *new_argv[4];

  new_argv[0] = "ping";
  new_argv[1] = "-c";
  new_argv[2] = "3";
  new_argv[4] = NULL;

  for(i=1; i<argc ; i++){
    if((pid = fork()) == 0){
      /*child prosess*/
      new_argv[3] = argv[i];
      execvp("ping", new_argv);
      perror("ping");
      exit(1);
    }
 

  /*parent process*/
  if(pid == -1){
    perror("fork");
    exit(1);
  }

  if((w = wait(NULL)) == -1 ){
    perror("wait");
    exit(1);
  }

  }

  exit(0);
}
