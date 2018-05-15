#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
void*nthPrime(void*);
int main(int argc, char**args)
{
  if(argc==1)
  {
    fprintf(stderr, "Invalid number of agrs\n");
  }
  else
  {
    void *ptr;
void **arr = malloc(sizeof(void *) * (argc-1));
for (int i = 0; i < (argc-1); i++) {
    arr[i] = ptr;
}

    pthread_t* tid = (pthread_t*)malloc(sizeof(pthread_t)*(argc-1));
    for(int i = 0; i<argc-1;i++)
    {
      pthread_create(&tid[i],NULL,nthPrime,(void*)args[i+1]);
      pthread_join(tid[i],&arr[i]);
    }
    for(int i = 0; i<argc-1;i++)
    {
      printf("%sth prime is: %d\n",args[i+1],*(int*)arr[i]);
    }
  }
}
void*nthPrime(void*args)
{
  char *ch = (char*)args;
  int n = atoi(ch);
  long *candidate = (long*)malloc(sizeof(long));
  *candidate = 2;
  while(1)
  {
    long factor;
    int is_prime = 1;
    for(factor=2;factor<=sqrt((*candidate));++factor)
    {
      if((*candidate)%2==0)
      {
        is_prime = 0;break;
      }
      if((*candidate)%factor==0)
      {
        is_prime = 0; break;
      }
    }
    if(is_prime==1)
    {
      n--;
    }
    if(n==0)
    {
      pthread_exit((void*)(candidate));
    }
    ++(*candidate);
  }
}
