#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BSIZE 500
char buf[BSIZE];



main(int argc, char **argv){

  int pid1, pid2, p_fd[2], i, fb;
  char *new_program, *new_argv[argc-2];

  if(argc < 2){
    fprintf(stderr, "usage: %s command arg...\n",argv[0]);
    exit(0);
  }

  new_program =argv[2];//program for execvp
  new_argv[0] = argv[2];
  for(i = 3; i < argc; i++){
    new_argv[i-2] = argv[i]; 
 }
  new_argv[argc-2] = NULL;

  char *fn;
  fn = argv[1];
if((fb = open(fn, O_WRONLY|O_CREAT|O_TRUNC, 0644)) <0){
    perror(fn);
    exit(1);
  }

  pipe(p_fd);
  if((pid1 = fork()) == 0){
    //child process
    if((pid2 = fork()) == 0){
      close(p_fd[0]);
      close(1);
      dup(p_fd[1]);
      close(p_fd[1]);
   
      execvp(new_program, new_argv);
      perror(new_program);
      exit(0);
    }

    //parent process
    if(pid2 == -1){
      perror("fork");
      exit(1);
    }
      close(1);
      dup(fb);
      close(fb);
   
      execvp(new_program, new_argv);
      perror(new_program);
      exit(0);
  }

  close(p_fd[1]);
  close(0);
  dup(p_fd[0]);
  close(p_fd[0]);


  execvp(new_program, new_argv);
  perror(new_program);
  exit(0);

}
