/*
**	fnction takes two integer variables, add them using bitwise operators
**	and print the result.
*/
#include<stdio.h>
void addBitwise(int num1, int num2)
{

	int nu1 = num1;
	int nu2 = num2;
	int result=1;
	int res2=0;

	while(nu2!=0)
	{
		int carry = nu1 & nu2;
		nu1 = nu1 ^nu2;
		nu2 = carry <<1;
	}
	printf("Result of Addition: %d \n", nu1);
}
