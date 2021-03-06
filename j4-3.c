#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BSIZE 500
char buf[BSIZE];

/*filecp(int from, char *to_fd){
  int to;
  if((to = open(to_fd, O_WRONLY|O_CREAT|O_TRUNC, 0644))<0){
    perror(to_fd);
    exit(1);
  }
 while((read(from, buf,BSIZE)) > 0){
    if(write(to, buf, BSIZE) == -1){
      perror(to_fd);
      exit(1);
    }
  }
 lseek(from,0,SEEK_SET);
 }*/

main(int argc, char **argv){

  int pid1, pid2, p_fd[2], i, fb;
  char *new_program, *new_argv[argc-2];

  if(argc < 2){
    fprintf(stderr, "usage: %s command arg...\n",argv[0]);
    exit(0);
  }
  if((fb = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0644))<0){
    perror(argv[1]);
    exit(1);
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
    //if((pid2 = fork()) == 0){
      int n;
      /*close(1);
    dup(fb);
    close(fb);
  
    execvp(new_program, new_argv);
    perror(new_program);*/
      while((n = read(0, buf,BSIZE))>0){
	write(fb,buf,n);
      }
      //exit(1);
      //}

    //child process

    /*if(pid2 == -1){
      perror("fork");
      exit(1);
      }*/
    lseek(0,0,SEEK_SET);
    close(p_fd[0]);
    close(1);
    dup(p_fd[1]);
    close(p_fd[1]);
  
    execvp(new_program, new_argv);
    perror(new_program);
    exit(0);
  }

  close(p_fd[1]);
  close(0);
  //close(1);
  dup(p_fd[0]);
  //dup(fb);
  close(p_fd[0]);
  //close(fb);

  execvp(new_program, new_argv);
  perror(new_program);
  exit(0);

}
