In this problem you will create makefile for multi file C program.
 
prepare a makefile named Makefile_v1 that perform the compilation and linking of files. 
Your makefile 
>Should contains special target "all" that specify myapp as target.
>Should contains phony target clean. On executing "makefile clean" it will remove all the object files. 
>If object files not present then makefile should ignore errors.
>Should contains Macros.
>Should use Special Internal Macros where possible.
>Should contains target install that will be dependent on myapp. Target "install" will copy myapp executable
to directory /usr/local/bin and then echo Installed Successfully.
>Design the source code in two directories so as to write another make file and call it using include directive.
	



