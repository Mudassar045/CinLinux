#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
extern int errno;
int main()
{
  int nv = nice(+0);
  printf("Original value is: %d\n",nv );
  nv =(+6);
  printf("Incremented nice value by 6:%d\n",nv);
  errno = 0;
  nv = nice(-20);
  if(nv==-1 && errno!=0)
  {
    perror("nice(-20) failed");
    exit(1);
  }
  printf("Decremented nice value by-2: %d",nv);
  return 0;
}
