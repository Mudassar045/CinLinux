#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sched.h>
extern int errno;
int main()
{
  int rv =  sched_getscheduler(0);
  if(rv==0)
  {
    printf("Normal\n");
  }
  if(rv)
  printf("Fifo\n");
  return 0;
}
