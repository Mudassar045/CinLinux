#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <unistd.h>
int main(int agrc, char**argv)
{
  int fd = open(argv[1], O_RDONLY);
  int newfd = dup(fd);
  printf("Value before fork:%d\n", newfd);
  int fv = fork();
  if(fv==0)
  {
    int newfd = dup(fd);
    printf("Value after fork:%d\n", newfd);
    exit(0);
  }
}
