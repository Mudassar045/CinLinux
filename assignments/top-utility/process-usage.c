#include <sys/resource.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
	errno = 0;
	struct rusage* memory = malloc(sizeof(struct rusage));
	getrusage(RUSAGE_SELF, memory);
	if(errno == EFAULT)
	    printf("Error: EFAULT\n");
	else if(errno == EINVAL)
	    printf("Error: EINVAL\n");
	printf("Usage: %ld\n", memory->ru_ixrss);
	printf("Usage: %ld\n", memory->ru_isrss);
	printf("Usage: %ld\n", memory->ru_idrss);
	printf("Max: %ld\n", memory->ru_maxrss);
return 0;
}
