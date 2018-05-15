#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
int**A;
int**B;
int**C;
int step_i = 0;
struct mystruct
{
  int rows;
  int cols;
};
void* MUL(void* args)
{
  struct mystruct p = *(struct mystruct*)args;
  int core = step_i++;
  // Each thread computes 1/4th of matrix multiplication
  for (int i = core * p.rows / p.rows; i < (core + 1) * p.rows / p.rows; i++)
  for (int j = 0; j < p.cols; j++)
  for (int k = 0; k < p.cols; k++)
  C[i][j] += A[i][k] * B[k][j];
}
int main(int argc, char**args)
{
  if( argc != 2 )
  {
    printf("must enter the file name\n usage\t./a.out filename\n");
    return 1;
  }
  FILE *myFile;
  myFile=fopen(args[1],"r");		/*	opening file	*/

  int f_row, f_col;
  int s_row, s_col;
  int  i, j = 0;

  if(myFile==NULL)
  {
    printf("Error Reading File \n ");
  }

  fscanf(myFile,"%d",&f_row);
  fscanf(myFile,"%d",&f_col);
  //	int ** A;

  for (i=0; i<f_row; i++)
  A[i] = (int *)malloc(f_col * sizeof(int));
  for(i=0;i<f_row;i++){
    j = 0;
    do {
      fscanf(myFile, "%d", &(A[i][j]));
      j++;
    } while(j<f_col);
  }
  printf("First Matrix:\n");
        for(i=0;i<f_row;i++){
                for(j=0;j<f_col;j++){
                       printf("%d ",A[i][j]);
                }
                printf("\n");
        }
  fscanf(myFile,"%d",&s_row);
  fscanf(myFile,"%d",&s_col);

  for (i=0; i<f_row; i++)
  B[i] = (int *)malloc(s_col * sizeof(int));
  for(i=0;i<s_row;i++){
    for(j=0;j<s_col;j++){
      fscanf(myFile,"%d",&B[i][j]);
    }
  }
  printf("Second Matrix:\n");
        for(i=0;i<s_row;i++){
                for(j=0;j<s_col;j++){
                       printf("%d ",B[i][j]);
                }
                printf("\n");
        }
  /*
  for (i=0; i<f_row; i++)
  C[i] = (int *)malloc(s_col * sizeof(int));

  struct mystruct s1;
  s1.rows = f_row;
  s1.cols = s_col;

  pthread_t* tid = (pthread_t*)malloc(sizeof(pthread_t)*(f_row));
  for(int i = 0; i<f_row;i++)
  {
    pthread_create(&tid[i],NULL,MUL,(void*)&s1);
    pthread_join(tid[i],NULL);
  }
  for (int i = 0; i < f_row; i++) {
        for (int j = 0; j <s_col; j++)
            printf("%d ",C[i][j]);
        printf("\n");
    }
    */
}
