#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
void*f1(void*);
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
      pthread_create(&tid[i],NULL,f1,(void*)args[i+1]);
      pthread_join(tid[i],&arr[i]);
    }
    for(int i = 0; i<argc-1;i++)
    {
      printf("Character count of %s is: %d\n",args[i],*(int*)arr[i]);
    }
  }
}
void*f1(void* args)
{
  char* filename = (char*)args;
  int *result = (int*)malloc(sizeof(int));
  *result = 0;
  char ch;
  int fd = open(filename,O_RDONLY);
  while((read(fd,&ch,1))!=0){
    (*result)++;
  }
  close(fd);
  pthread_exit((void*)result);
}
