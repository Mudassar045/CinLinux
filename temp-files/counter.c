#include <stdio.h>
#include <string.h>
void main(int argc, char** argv)
{
	char s[1000];
	int count = 0;
	FILE *fp;
	fp = fopen(argv[1], "r");
	while(fgets(s,64,fp)!=NULL)
	{
		count += strlen(s);
	}
	printf("Number of characters are: %d\n", count);	
}