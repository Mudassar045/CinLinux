/*
* check whether a string entered by the user is an alphabet or not.
* prompt result on screen whether a string is alphabet or not
*/


void check_alphabet(char s[]) {
  // write your code
  bool flag = false;
  for(int i = 0; s[i]!='\0';i++)
  {
    if(s[i]>='a' && s[i]<='z')
    {
      flag = true;
    }
    else if(s[i]>='A' && s[i]<='Z')
    {
      flag = false;
    }
    else
    {
      flag = false;
      break;
    }
    if(flag)
    {
      printf("%s is upper string\n",s);
    }
    else
    {
      printf("%s is upper string\n",s);
    }
  }

}
