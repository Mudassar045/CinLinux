#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main (int argc, char *argv[])
{
  struct stat sb;
  int ret;
  if (argc < 2)
  {
    fprintf (stderr,
      "usage: %s <file>\n", argv[0]);
      exit(1);
    }
    ret = stat (argv[1], &sb);
    if (ret)
    {
      perror ("stat");
      exit(1);
    }
    printf("%s is %ld bytes\n",argv[1], sb.st_size);
    printf("%s is %ld bytes\n",argv[1],sb.st_blksize);
    exit(0);
  }
