#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <unistd.h>
int main(int agrc, char**argv[])
{
  char buff[100];
  char cbuff[100];
  int fd = open(argv[1], O_RDONLY);
  printf("Enter your information:");
  fgets(buff,100, stdin);
  printf("%s\n", buff);
  close(0);
  int newfd = dup(fd);
  //printf("%d\n",newfd);
  int byte_read = read(newfd,cbuff,100);
  write(1,cbuff,byte_read);
  //printf("%d\n", newfd);
  exit(0);
}
