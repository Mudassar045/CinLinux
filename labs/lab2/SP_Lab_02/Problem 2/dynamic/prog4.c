/*
**	functions takes one integer variable and convert it into hexadecimal
**	and print the converted number on stdout.
*/
#include<stdio.h>
void toOctal(unsigned int num)
{

	unsigned int mask = 7;
	char result[10]={0} ;

    	static char OCT[] = "01234567";

    	// represents the end of the string.
    	int index = 9;
	int i =9;
    	while (num > 0 )
	{
        	result[i]=OCT[(num & mask)];
        	num >>= 3;
		i--;
    	}
	printf("Octal Eqivalent  : ");
	for(int i =0; i< 10; i++)
	{
		printf("%c", result[i]);
	}
	printf("\n");
}
