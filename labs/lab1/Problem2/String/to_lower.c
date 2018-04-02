/*
// ASCII value of 'A' is 65 while 'a' is 97. Difference between them is 97 – 65 = 32
// So if we will add 32 in the ASCII value of 'A' then it will be 'a'
// and if will we subtract 32 in ASCII value of 'a' it will be 'A'. It is true for all alphabets.
// In general rule:
// Upper case character = Lower case character – 32
// Lower case character = Upper case character + 32
*/

/* convert lowercase character to uppercase */

int to_lower(int a)
{
    // here write your code
    if(a>=97 && a<=122)
    {
      a = a;
    }
    else if(a>=65 && a<=90)
    {
      a+=32;
    }
    return a;
}
