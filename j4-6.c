#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
main(int argc, char **argv)
{

  char *new_argv[argc];

  new_argv[0] = argv[1];
  int i=1;
  while(argv[i] != NULL){
    new_argv[i] = argv[i+1];
    i++;
  }
  execvp(argv[1], new_argv);
}
