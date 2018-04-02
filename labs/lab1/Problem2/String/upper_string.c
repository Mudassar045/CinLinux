/*
// ASCII value of 'A' is 65 while 'a' is 97. Difference between them is 97 – 65 = 32
// So if we will add 32 in the ASCII value of 'A' then it will be 'a'
// and if will we subtract 32 in ASCII value of 'a' it will be 'A'. It is true for all alphabets.
// In general rule:
// Upper case character = Lower case character – 32
// Lower case character = Upper case character + 32
*/

/* Convert lowercase in string to uppercase */

void upper_string(char s[]) {
   // write your code
  for(int i = 0; s[i]!='\0';i++)
  {
    if(s[i]>='a' && s[i]<='z')
    {
      s[i]=s[i]-32;
    }
    else
    {
      s[i] = s[i];
    }
  }
}
