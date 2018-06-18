#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main()
{
  int pid ,w;

  if((pid = fork()) == 0){
    execl("/bin/ls", "ls", "-la", NULL);
    perror("/bin/ls");
    exit(1);
  }

  if(pid == -1){
    perror("fork");
    exit(1);
  }

  printf("/bin/ls: done\n");
  exit(0);
}
