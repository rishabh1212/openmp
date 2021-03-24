/*
Integration using OPENMP

Target Function to Integrate from 0 to 1: 4 / (1 + x^2) w.r.t x
Expected output: pi

Idea: Sum of area under the curve ~ sum of area of large number of rectangles under the curve

False Sharing(double areas[NUM_THREADS])
-------------
If independent data variables tend to sit on same cache line, so if some variable is changed by some thread then data is invalidated.
Affects performance, to avoid this make sure independent variables are not on same cache line or use synchronization
*/

#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 4

int main()
{
    int total_num_rectangles = 100000000;
    double rect_width = 1.0 / total_num_rectangles;
    double areas[NUM_THREADS];
    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        //There is a chance that number of requested threads is not same as number of assigned threads
        int ASSIGNED_NUM_THREADS = omp_get_num_threads();
        double total_width_per_thread = 1.0 / ASSIGNED_NUM_THREADS;
        double start_x = thread_num * total_width_per_thread;
        int num_per_thread = total_num_rectangles / ASSIGNED_NUM_THREADS;
        areas[thread_num] = 0.0;
        for(int i=0; i<num_per_thread; i++)
        {
            areas[thread_num] += rect_width * (4.0 / (1.0 + (start_x * start_x)));
            start_x += rect_width;
        }
    }
    double total = 0.0;
    for(int i=0; i<NUM_THREADS; i++) total += areas[i];
    printf("%f", total);
}

