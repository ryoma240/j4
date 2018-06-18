#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BSIZE 512
char buf[BSIZE];

void
mkfile (int fd, int size)
{

  while(size > BSIZE){
    lseek(fd,BSIZE,SEEK_CUR);
    size -=BSIZE;
  }

  write(fd, buf,size);
}

main(int argc, char **argv)
{
  int fd, size;
  if(argc != 3){
    fprintf(stderr, "usage: %s size filename\n", argv[0]);
    exit(1);
  }
  size = atoi(argv[1]);
  fd = open(argv[2], O_WRONLY| O_CREAT| O_TRUNC, 0644);

  printf("sizev= %d, fd = %d\n", size, fd );

  if(fd<0){
    perror(argv[2]);
    exit(1);
  }
  mkfile(fd, size);

  close(fd);
  exit(0);
}
