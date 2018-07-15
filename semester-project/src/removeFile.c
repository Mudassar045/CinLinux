/*
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_BYTES 1024
#define MAX_CHARS 1024

static const char *concat(const char *s1, const char *s2);
int removeFile(char *filename)
{
  struct stat mystat;
  char buff[MAX_CHARS];
  int rv = stat(filename, &mystat);
  int mode_t = mystat.st_mode;

  int fdf = open(filename, O_RDONLY);
  char *newfile = concat(".mdrm_temp/", filename);
  int fds = open(newfile, O_TRUNC | O_CREAT | O_RDWR, mode_t);
  if (fds == -1)
  {
    fprintf(stderr, "rm: unable to remove file");
    exit(0);
  }
  else
  {
    while (1)
    {
      int byte_t = read(fdf, buff, MAX_BYTES);
      if (byte_t <= 0)
      {
        break; // file reading complete
      }
      write(fds, buff, byte_t);
    }
  }
  close(fdf); // file descriptor for original file
  close(fds); // file descriptor for trash file
  rv = remove(filename);
  if (rv == -1)
  {
    fprintf(stderr, "rm: unable to perform remove operation");
    return -1;
  }
  else
    return 0;
}

static const char *concat(const char *s1, const char *s2)
{
  char *result = malloc(strlen(s1) + strlen(s2) + 1); //+1 for the null-terminator
  //in real code you would check for errors in malloc here
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}
*/