#include <stdio.h>
void foo(void)
{
   printf("%s",__func__);
}
void bar(void)
{
   printf("%s",__func__);
}
int main()
{
   //foo();
   //bar();
   printf("File Name:%s\nFunction Name:%s()\nCurrent printf() line:%d\n",__FILE__,__func__,__LINE__);
   return 0;
}