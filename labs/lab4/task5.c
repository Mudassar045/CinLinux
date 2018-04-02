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
  int flags = fcntl(fd, F_GETFL, 0); //get settings
  flags = flags | O_SYNC;
  //modify settings
  fcntl(fd, F_SETFL, flags);
  //set them back
  int rv = write(fd,buff,sizeof(buff));
  if(rv==-1)
  {
    fprintf(stderr, "Error occured while writing to disk\n");
    exit(1);
  }
  else
  {
    fprintf(stdout, "Contents successfully written\n");
  }
  exit(0);
}
