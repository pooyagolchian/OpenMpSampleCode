#include <stdio.h>
#include <omp.h>

int main (void)
{
    #pragma omp parallel num_threads(20)
    printf("Hello, World!\n");
    return 0;
}
