#include<stdio.h>
#include<stdlib.h>
static int disable_my_exit_handler =0;
void exit_handler_1()
{
    if ( disable_my_exit_handler )
        return;
    printf("in first exit handler\n");
}
void exit_handler_2()
{
    printf("%d\n",45);

}
int main( void )
{
    printf("In main proc\n");
    if ( atexit( exit_handler_1 ) )
    {
        perror("error");
    }
    if(atexit( exit_handler_2))
    {
      perror("error");
    }
    disable_my_exit_handler = 0;
    return abort();

}
