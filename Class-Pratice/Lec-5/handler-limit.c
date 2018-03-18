#include <stdio.h>   //for perror function
#include <stdlib.h> //for exit and atexit function
#include <unistd.h> //for _exit system call

void exit_handler(){
   printf("Exit handler\n");
}
int main()
{
   int counter = 0;
   int check = 0;
   while(1)
  {
    check = atexit(exit_handler);
    printf("%d\n",counter++);
    if(check<0)
    {
     perror("error");
    }
  }
   printf("Main is done!\n");
   exit(counter);
}
