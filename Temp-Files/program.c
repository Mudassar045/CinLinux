#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
struct Operands
{
	int num1;
	int num2;
};
void* CalculatePower(void *agrs)
{
	struct Operands *p = (struct Operands *)agrs;
	int n1 = p->num1;
	int n2 = p->num2;
	printf("The power is: %.0f\n", pow(n1,n2));
}
int main(int argc, char* args[])
{
	int pNum1 = 0;
	int pNum2 = 0;
	pthread_t tid;
	struct Operands* t1_pow;
	char * a1 = args[1];
	char * a2 = args[2];
	pNum1 = atoi(a1);
	pNum2 = atoi(a2);
	t1_pow->num1=pNum1;
	t1_pow->num2=pNum2;
	int rv = pthread_create(&tid,NULL, &CalculatePower, (void*)t1_pow);
	if(rv!=0)
	{
		printf("Thread Creation failed");
		exit(1);
	}
	pthread_join(tid, NULL);
	while(1)
	{;}
	return 0;
}	
