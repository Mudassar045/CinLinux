#include <stdio.h>
#include <stdlib.h>
#include <myfuncs.h>
int main(void)
{
  int num1 = 15;
  int num2 = 45;
  printf("Adding By Bitwise\n");
  addBitwise(num1,num2);
  printf("Bit Range\n");
  if(isBitSetInRange('A', 65, 91))
  {
    printf("Yes in range\n");
  }
  else
  {
    printf("No, not in range\n");
  }
  printf("Conversion to Binary\n");
  toBinary(num1);
  printf("Conversion to Octal\n");
  toOctal(num1);
  return 0;
}
