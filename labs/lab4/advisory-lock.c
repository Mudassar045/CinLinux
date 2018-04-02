#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
  if (argc >= 1)
  {
    int fd = open(argv[1], O_WRONLY);
    if(fd == -1)
    {
      printf("Unable to open the file\n");
      exit(1);
    }
    static struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;
    lock.l_pid = getpid();

    int ret = fcntl(fd, F_SETLK, &lock);
    if(ret==-1)
    {
      printf("You can't acquire the lock\n");
      exit(1);
    }
    printf("Lock sucessfully acquired\n");
    while (1){}
  }
  else
  {
    printf("Missing file name\n");
    exit(0);
  }
}
