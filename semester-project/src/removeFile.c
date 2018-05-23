#include <fcntl.h>
#include <stdio.h>
#include <string.h>
int removeFile(char* filename)
{
  int fdf = open(filename,O_RDONLY);
  char *newfile = strcat("/home/special_files/",filename);
  int fds = open(newfile,O_CREAT|O_TRUNC|O_RDWR,0600);
  return 0;
}