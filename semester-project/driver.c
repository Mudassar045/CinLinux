#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
extern int errno;
int isFile(char *filename);
int isDir(char *dirname);
int main(int argc, char**args)
{
  if(argc==1)
  {
   fprintf(stderr, "rm: missing operands\nTry 'rm --help' for more information.\n");
  }
  else if(argc==2 && isFile(args[1]))
  {

  }
  else if(argc==2 && isDir(args[1]))
  {

  }
  else if(argc==3 && isFile(args[1]) && strcmp(agrs[2]=="i"))
  {
    if(isRegularFile(args[1]) && isEmpty(args[i]))
    printf("rm: remove Are you sure to delete (Y/N)?");
    char ch = getchar();

  }
  else
  {
    printf("Has commandline args\n");
  }
  return 0;
}
