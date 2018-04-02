#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <unistd.h>
int main(int agrc, char**argv)
{
  int fd = open(argv[1],O_RDONLY);
  int ret;
  /*
  * Setting the file perms for owner
  */
   ret = fchmod(fd, S_IRUSR|S_IWUSR);
   if(ret)
   {
     perror("fchmod");
   }
   else
   {
     fprintf(stdout, "file perms changed successfully\n");
   }
   exit(0);
}
