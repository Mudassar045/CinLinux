/*
*  Video Lecture: 08
*  Programmer: Arif Butt
*  Course: System Programming with Linux
*/
#include <stdio.h>   //for perror function
#include <stdlib.h> //for exit and atexit function
#include <unistd.h> //for _exit system call

void exit_handler(){
   printf("Exit handler\n");
}
void myexit(int exitStatus, void *arg){
	printf("Exit Handler called with exit status=%d and arg=%ld\n", exitStatus, (long)arg);
}
int main(){
   on_exit(myexit,(void*)7);
   atexit(exit_handler);
   printf("Main is done!\n");
   //return 0;  or exit(0);
exit(1);
   //_exit(54);
}
