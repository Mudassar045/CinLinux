#include <stdio.h>
#include <stdlib.h>
#define BLOCK_SIZE 512
void filecopy(FILE*, FILE*);
void StdinToStdout();
void append(char *str, char ch);
int main(int argc, char*argv[])
{
  FILE *iptr, *optr;
  char ipchars[1024];
  int scanRet = 0;
  if(argc==1)
  {
    while(1)
    {
      char c = getchar();
      if(c == '\n')
      {
        printf("%s",ipchars);
        memset(ipchars, 0, sizeof ipchars);
      }
      append(ipchars,c);
    }
  }
else
{
  iptr = fopen(argv[1], "r");
  if (iptr == NULL)
  {
    fprintf(stderr, "%s: %s: No such file or directory\n",argv[0],argv[1]);
    exit(1);
  }
  // Open another file for writing
  optr = fopen(argv[2], "w");
  if (optr == NULL)
  {
    fprintf(stderr, "%s: can't open %s\n",argv[0], argv[2]);
    exit(1);
  }
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
    fputc(c, stdout);
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
void append(char* str, char c) {
  int len = strlen(str);
  str[len] = c;
  str[len+1] = '\0';
}
