/*
  Name: rm-urm utility
  Environment: Linux based operating system
  Developer: Mudassar Ali
  Resident: Lahore, Pakistan
  Language: GNU C
  Version: 1.0.0
*/
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "rmutils.h"
#include "urmutils.h"

extern int errno;

int isFile(char *filename);
int isDir(char *dirname);
int isRegularFile(char* filename);
int isEmpty(char* filename);
int makeTempDir(char* dirname);
int main(int argc, char**args)
{
  int rv = makeTempDir(".mdrm_temp");
  if(argc==1)
  {
    fprintf(stderr, "rm: missing operands\nTry 'rm --help' for more information.\n");
  }
  else if(argc==2 && isFile(args[1]))
  {
    int rv = removeFile(args[1]);
      if(rv==0)
      {
        return 0;
      }
      else
      {
        fprintf(stderr,"rm: unable to delete a file\n");
      }
  }
  else if(argc==2 && isDir(args[1]))
  {
    removeDir(args[1]);
  }
  else if(argc==3 && isFile(args[1]) && strcmp(args[2],"i")==0)
  {
    if(isRegularFile(args[1]) && isEmpty(args[1]))
    {
      printf("rm: remove regular file (Y/n)? ");
      char ch = getchar();
      if(ch=='Y' || ch=='y')
      {
        int rv = removeFile(args[1]);
        if(rv==0)
        {
          printf("file has been deleted\n");
          return 0;
        }
        else
        {
          fprintf(stderr,"rm: unable to delete a file\n");
        }
      }
      else
      {
        fprintf(stderr,"rm: invalid option");
      }
    }
    else
    {
      return 0;
    }

  }
  else
  {
    printf("Has commandline args\n");
  }
  return 0;
}
int makeTempDir(char* dirname)
{
  int rv = mkdir(dirname);
  return rv;
}
int isFile(char* filename)
{
  return 1;
}
int isDir(char* dirname)
{
  return 1;
}
int isRegularFile(char* filename)
{
  return 1;
}
int isEmpty(char* filename)
{
  return 1;
}