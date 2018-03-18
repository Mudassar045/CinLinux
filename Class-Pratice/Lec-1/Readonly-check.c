#include<stdio.h>
#include<stdlib.h>
int main()
{
 char *str;
 str = "GfG";     /* Stored in read only part of data segment */
 *(str+1) = 'n'; /* Problem:  trying to modify read only memory */
 getchar();
 return 0;
}
