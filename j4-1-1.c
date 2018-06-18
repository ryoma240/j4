#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


#define BSIZE 500
char buf[BSIZE];

void
file_copy(char *from ,char *to){
  int from_fd, to_fd;

  from_fd = open(from, O_RDONLY);

  if(from_fd < 0){
    perror( from);
    exit(1);
  }

  to_fd = open(to, O_WRONLY|O_CREAT|O_TRUNC, 0644);

  if(to_fd < 0){
    perror( to );
    exit(1);
  }

  printf("from_fd =%d, to_fd = %d\n", from_fd, to_fd);

  while((read(from_fd, buf,BSIZE)) > 0){
    if(write(to_fd, buf, BSIZE) == -1){
      perror(to);
      exit(1);
    }
  }
}

main(int argc, char **argv)
{
  int fd, size;

  if(argc != 3){
    fprintf(stderr, "usage: %s size filename\n", argv[0]);
    exit(1);
  }

  file_copy(argv[1], argv[2]);
  close(argv[1]);
  close(argv[2]);

}
