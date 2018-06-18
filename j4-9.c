#include <stdio.h>
#include <stdlib.h>

main (int argc, char **argv)
{
  int pid,i;

  for(i = argc; i > 0; --i){
    if((pid = fork()) == 0){
      printf("%s\n", argv[argc-i]);
      exit(0);
    }

    if(pid == -1){
      perror("fork");
      exit(1);
    }
  }
  for(i = argc; i >0; --i){
    if(wait(NULL) == -1){
      perror("wait");
      exit(1);
    }}

  exit(0);
}
