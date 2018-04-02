/*
**	functions takes one integer variable and convert it into binary
**	and print the converted number on stdout.
*/
#include<stdio.h>
void toBinary(unsigned int num)
{

	unsigned int mask=32768;   //mask = [1000 0000 0000 0000]
	printf("Binary Eqivalent : ");

	while(mask > 0)
	{
	   if((num & mask) == 0 )
		 printf("0");
	   else
		 printf("1");
	  mask = mask >> 1 ;  // Right Shift
	}
	printf("\n");

}
