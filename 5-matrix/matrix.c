#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
int main()
{
	int *a,*b,*c;
	int i,j,k,n,m,sum;
	int seconds;
	time_t t1,t2;
	printf("Enter the no of rows in the matrix : ");
	scanf(" %d",&n);
	printf("Enter no of cols in the matrix : ");
	scanf(" %d",&m);
	a=(int*)malloc(n*m*sizeof(int));
	b=(int*)malloc(n*m*sizeof(int));
	c=(int*)malloc(n*m*sizeof(int));
	printf("\nProcessing SERIAL block of code...\n");
	t1=time(NULL);
	for(i=0;i<n;i++)
	{ for(j=0;j<m;j++)
		{ *(a+i*m+j)=2;
		  *(b+i*m+j)=1;
		}
	}
	for(i=0;i<n;i++)
	{ for(j=0;j<m;j++)
		{ sum=0;
		  for(k=0;k<m;k++)
		    sum=sum+(*(a+i*m+k))*(*(b+k*m+j));
	      *(c+i*m+j)=sum;
	    }
	}
	t2=time(NULL);
	seconds=difftime(t2,t1);
	printf("\nBlock of code running SERIALLY took %d seconds\n\n",seconds);
	free(a);
	free(b);
	free(c);

	/******  Parallel Code *********/

	a=(int*)malloc(n*m*sizeof(int));
	b=(int*)malloc(n*m*sizeof(int));
	c=(int*)malloc(n*m*sizeof(int));
	t1=time(NULL);
        printf("Processing PARALLEL block of code...\n");
	for(i=0;i<n;i++)
	{ for(j=0;j<m;j++)
		{ *(a+i*m+j)=2;
		  *(b+i*m+j)=1;
		}
	}

	omp_set_num_threads(10);
	#pragma omp parallel for private(i,j,k)  ordered schedule(runtime)
	for(i=0;i<n;i++)
	{ for(j=0;j<m;j++)
	  { sum=0;
	    #pragma omp parallel for num_threads(10) reduction(+:sum)
	    for(k=0;k<m;k++)
		  sum=sum+(*(a+i*m+k))*(*(b+k*m+j));
	    *(c+i*m+j)=sum;

      }
	}
	t2=time(NULL);
	seconds=difftime(t2,t1);
	printf("\nBlock of code running PARALLELY took %d seconds\n\n",seconds);
	free(a);
	free(b);
	free(c);
	return 0;
}
