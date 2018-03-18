// A recursive C program to print all numbers from 1
// to N without semicoolon
#include<stdio.h>
#define N 10
 
int main(int num)
{
    if (num <= N && printf("%d ", num) && main(num + 1))
    {
    }    
}