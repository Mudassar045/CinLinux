#include<stdio.h>
#include<stdlib.h>
#include <termios.h>
#include <unistd.h>
void filecopy(FILE *, FILE *);
int getch(FILE *f);
int main(int argc, char *argv[])
{
	FILE *fp;
	char *prog = argv[0];
	if(argc==1)
		filecopy(stdin, stdout);
	else
	while(--argc > 0)
		if((fp = fopen(*++argv, "r"))==NULL)
		{
			fprintf(stderr, "%s: can't open %s\n",prog, *argv);
			 exit(1);
		}
		else
		{
				filecopy(fp, stdout);
				fclose(fp);
		}
	if(ferror(stdout))
		{
				fprintf(stderr,"%s: error writing stdout\n",prog);
				exit(2);
		}
		exit(0);
}
void filecopy(FILE *f1, FILE *f2)
		{
		   char c = fgetc(f1);
			while (c != EOF)
			{
				fputc(c, f2);
				c = fgetc(f1);
			}
		}
