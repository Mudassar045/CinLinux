#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/*int main()
{
	int s1[]={25};
	int s[]={3,6,9,12,18};
	int *p=+s1;
	p=+s;
	printf("%d",(int)p[0]);
}*/
int main(void)
{
   printf("this is one line\n");
   pid_t pid = fork();
   pid = fork();
   pid = fork();
   if ( pid == 0 )
       fork();
   fork();
       printf("this is one line\n");
}
