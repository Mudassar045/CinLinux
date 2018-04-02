/*

* An integer is a palindrome if the reverse of that number is equal to the original number.
* For example, 1221 and 2332 are two palindrome numbers
* write code to check whether number is palindrome or not
* if true return 1 else 0*/


int Palindrome(int number1)
{
    // write your code here
   int temp  = number1;
   int rem = 0;
   while(number1!=0)
   {
     rem = rem*10+(number1%10);
     number1/=10;
   }
   if(number1==temp)
   return 1;
   else
   return 0;

}
