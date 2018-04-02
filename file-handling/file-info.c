#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main (int argc, char *argv[])
{
  struct stat sb;
  int fd = open(argv[1],"r");
  int ret;
  if (argc < 2)
  {
      fprintf (stderr,"usage: %s <file>\n", argv[0]);
      exit(1);
    }
    ret = stat (argv[1], &sb);
    if (ret)
    {
      perror ("stat");
      exit(1);
    }
    switch (sb.st_mode & S_IFMT) {
      case S_IFBLK:
      printf("block device node\n");
      break;
      case S_IFCHR:
      printf("character device node\n");
      break;
      case S_IFDIR:
      printf("directory\n");
      break;
      case S_IFIFO:
      printf("FIFO\n");
      break;
      case S_IFLNK:
      printf("symbolic link\n");
      break;
      case S_IFREG:
      printf("regular file\n");
      break;
      case S_IFSOCK:
      printf("socket\n");
      break;
      default:
      printf("unknown\n");
      break;
    }
    if(is_on_physical_device()==0)
    {
      printf("%s resides on physical device\n",argv[1]);
    }
    else
    {
      printf("%s resides on physical device\n",argv[1]);
    }
    exit(0);
  } // end of main
  /*
* is_on_physical_device - returns a positive
* integer if 'fd' resides on a physical device,
* 0 if the file resides on a nonphysical or
* virtual device (e.g., on an NFS mount), and
* −1 on error.
*/
  int is_on_physical_device (int fd)
  {
    struct stat sb;
    int ret;
    ret = fstat (fd, &sb);
    if (ret)
    {
      perror("fstat");
      exit(-1);
    }
    return gnu_dev_major (sb.st_dev);
  }
