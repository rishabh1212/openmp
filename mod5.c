/*
    Work Sharing
    Using OPENMP FOR trying to divide the work and then reduce
    Reduction use operator with variable, for the reduction operator local copies of threads are initialised with identity vals.
    EX: + is initialised with 0, * with 1, etc
*/
#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 4

static long num_steps = 1000000;
double step;
int main ()
{
    int i;
    double pi, sum = 0.0;
    step = 1.0/(double) num_steps;
    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel for reduction (+:sum)
    // Moved x from heap to thread stack
    for (i=0; i<num_steps; i++)
    {
        double x = (i+0.5)*step;
        sum = sum + 4.0/(1.0+x*x);
    }
    pi = step * sum;
    printf("%f", pi);
}