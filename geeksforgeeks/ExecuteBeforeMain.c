#include<stdio.h>
#include<stdlib.h>
 
/* Apply the constructor attribute to myStartupFun() so that it
    is executed before main() */
void myStartupFun1 (void) __attribute__ ((constructor));
void myStartupFun2 (void) __attribute__ ((constructor)); 
 
/* Apply the destructor attribute to myCleanupFun() so that it
   is executed after main() */
void myCleanupFun (void) __attribute__ ((destructor));
 
 
/* implementation of myStartupFun */
void myStartupFun1 (void)
{
    printf ("startup code 1 before main()\n");
}
void myStartupFun2 (void)
{
    printf ("startup code 2 before main()\n");
}
 
/* implementation of myCleanupFun */
void myCleanupFun (void)
{
    printf ("cleanup code after main()\n");
}
 
int main (void)
{
    printf ("hello\n");
    exit(0);
}