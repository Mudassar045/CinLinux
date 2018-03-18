#include <stdio.h>
int main()
{
  int  x = 10;
  int y  = 3;
  x = x^y;
  y = y^x;
  x = y^x;
  printf("x = %d\ny = %d\n",x,y);
  return 0;
}
