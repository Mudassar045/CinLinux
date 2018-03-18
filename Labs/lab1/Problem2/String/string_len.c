/*
*	Calculate Length of String without Using strlen() Function
*/

int string_len(char s[])
{
  int counter = 0;
 for (int i  = 0;s[i]!='\0'; i++) {
   /* code */
   counter++;
 }
 return counter;
}
