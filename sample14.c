#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

main(int argc, char **argv){

  int pid, p_fd[2];
  char *new_program, **new_argv;

  if(argc < 2){
    fprintf(stderr, "usage: %s command arg...\n",argv[0]);
    exit(0);
  }

  pipe(p_fd);
  if((pid = fork()) == 0){
    close(p_fd[0]);
    close(1);
    dup(p_fd[1]);
    close(p_fd[1]);

    new_program =argv[1];
    new_argv = &argv[1];
    execvp(new_program, new_argv);
    perror(new_program);
    exit(1);
  }

  if(pid == -1){
    perror("fork");
    exit(1);
  }

  close(p_fd[1]);
  close(0);
  dup(p_fd[0]);
  close(p_fd[0]);

  execl("/bin/more", "more", "-10", NULL);
  perror("/bin/more");
  exit(1);
}
