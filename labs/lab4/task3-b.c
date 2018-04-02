#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <unistd.h>
int main(int agrc, char**argv)
{
  char buff[100];
  int fd = open(argv[1], O_WRONLY);
  printf("Enter your information:");
  fgets(buff,100, stdin);
  //printf("%s\n", buff);
  int newfd = dup2(fd,1);
  close(fd);
  //printf("Value: %d\n",newfd);
  //int byte_read = read(fd,cbuff,100);
  write(1,buff,sizeof(buff));
  //printf("%d\n", newfd);
  exit(0);
}
