/*
* check whether a string entered by the user is an alphabet or not.
* prompt result on screen whether a string is alphabet or not
*/

#include <stdio.h>
#include <stdlib.h>
void check_alphabet(char s[]) {
  // write your code
  int flag = 0;
  for(int i = 0; s[i]!='\0';i++)
  {
    if(s[i]>='a' && s[i]<='z')
    {
      flag = 1;
    }
    else if(s[i]>='A' && s[i]<='Z')
    {
      flag = 1;
    }
    else
    {
      flag = 0;
      break;
    }
    if(flag==1)
    {
      printf("%s is upper string\n",s);
    }
    else
    {
      printf("%s is not upper string\n",s);
    }
  }

}
