#include<stdio.h>
int main()
{
  unsigned int i = 1;
  char *c = (char*)&i;
  if (*c)
  printf("LITTLE ENDIAN\n");
  else
  printf("BIG ENDIAN\n");
  return 0;
}
