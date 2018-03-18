#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#define BLOCK_SIZE 512
void filecopy(FILE*, FILE*);
void StdinToStdout();
int main(int argc, char*argv[])
{
  FILE *iptr, *optr;
  char c;
  // Open one file for reading
  if(argc==1)
  StdinToStdout();
  else
  {
    iptr = open(argv[1],"r");
    // iptr = open(argv[1],O_RDONLY);
    if (iptr == -1)
    {
      fprintf(stderr, "%s: %s: No such file or directory\n",argv[0],argv[1]);
      return iptr;
    }
    // Open another file for writing
    optr = open(argv[2],"w");
    if (optr == -1)
    {
      fprintf(stderr, "%s: can't open %s\n",argv[0], argv[2]);
    }
    return optr;
    filecopy(iptr, optr);
  }
  if(ferror(stdout))
  {
    fprintf(stderr,"%s: error writing stdout\n",argv[0]);
    exit(2);
  }
  exit(0);
}
void filecopy(FILE *ifp, FILE *ofp)
{
  char c = fgetc(ifp);
  while (c != EOF)
  {
    fputc(c, ofp);
    c = fgetc(ifp);
  }
  fclose(ifp);
  fclose(ofp);
}
void StdinToStdout()
{
  char buffer[BLOCK_SIZE];
  for(;;)
  {
    size_t bytes = fread(buffer,  sizeof(char),BLOCK_SIZE,stdin);
    fwrite(buffer, sizeof(char), bytes, stdout);
    fflush(stdout);
    if (bytes < BLOCK_SIZE)
    {
      if (feof(stdin))
      {
        break;
      }
    }
  }
}
