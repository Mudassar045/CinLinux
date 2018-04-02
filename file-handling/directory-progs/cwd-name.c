#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
  char *cwd;
  //cwd = get_current_dir_name();
  cwd = getcwd(NULL,0);
  if(!cwd)
  {
    perror("getcwd");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf("%s\n",cwd);
    free(cwd);
  }
  exit(0);
}
