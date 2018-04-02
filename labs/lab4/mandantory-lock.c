#include <sys/fcntl.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
  if (argc != 2)
  {
    fprintf(stderr, "File missing");
    exit(1);
  }
  int fd = open(argv[1], O_RDWR); // openning a file
  if (fd == -1)
  {
    fprintf(stderr, "Unable to open file\n");
    exit(1);
  }
  // WRITE lock
  struct flock lock1 = {};
  lock1.l_type = F_WRLCK;
  lock1.l_whence = SEEK_SET;
  lock1.l_start = 0;
  lock1.l_len = 0;
  // READ lock
  struct flock lock2 = {};
  lock2.l_type = F_RDLCK;
  lock2.l_whence = SEEK_SET;
  lock2.l_start = 0;
  lock2.l_len = 0;
  //lock.l_pid = getpid(); Mandatory locking is enabled on a file by disabling
  // group execute permission on the file
  if (fcntl(fd, F_SETLKW, &lock1) == -1 && fcntl(fd, F_SETLKW, &lock2) == -1)
  {
    printf("You can't acquire the file lock\n" );
    exit(1);
  }
  printf("File lock acquired succesfully\n");
  pause(); // while(1){}
  exit(0);
}
