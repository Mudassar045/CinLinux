#include <stdio.h>

/*
// Add missing header files here
*/

int main()
{
    int number1, number2;

    printf("Enter 1st number: ");
    scanf("%d",&number1);
    printf("Enter 2nd number: ");
    scanf("%d",&number2);

    printf("\n============== My Math Functions ===============\n");

    printf("Product = %d \n", multiply(number1, number2));
    printf("Power = %lld \n", power(number1, number2));
    int n =palindrome(number1);
	if(n==1)
    		printf("%d number is palindrom",number1);

    printf("\n=================================================\n\n");



    char string1[] = "Learning SP Is Fun";

    printf("\n============== My String Functions ===============\n");

    printf("Lower Case of A is = %c \n", to_lower('A'));

    upper_string(string1);
    printf("String in Upper Case is %s\n", string1);


    printf("\n=================================================\n");



   return 0;
}
