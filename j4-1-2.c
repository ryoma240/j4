#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void copy(FILE *fd1, FILE *fd2){
  int c;  /*文字格納*/

  while((c = fgetc(fd1)) != EOF){
    fputc(c, fd2);
  }

}

main(int argc, char **argv){
  FILE *fd1, *fd2;

  if(argc != 3){
    fprintf(stderr,"usage: %s size filename\n", argv[0]);
    exit(1);
      }


  if((fd1 = fopen(argv[1], "r")) == NULL){
    fprintf(stderr, "%s can not open\n", argv[1]);
    exit(1);
      }
  if((fd2 = fopen(argv[2], "w")) == NULL){
    fprintf(stderr, "%s can not open", argv[2]);
    exit(1);
  }

  copy(fd1, fd2);

  fclose(fd1);
  fclose(fd2);
  exit(0);
}
