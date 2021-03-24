/*
OPENMP: https://www.youtube.com/channel/UC7jgpE3sllixozoA4GzVRqQ

Kind of hardware openmp wants: Shared memory machines

2 Types of shared memory machines:

Symmetric Multiprocessor(SMP): OS gives equal time access to all processors, no special processor, no special memory block
Non Uniform Address Space Multiprocessor: Some addresses arefastly accessible from some processors and not others relatively
Modern multiprocessors not completely SMP, there is cache hirearchy in between and some processors can have faster access.

Fork-Join Parallelism in OPENMP
-------------------------------
Program starts as single thread - master thread
At some point of program instruction to fork new threads with master thread having id = 0, all threads share heap space having common variables.
All threads have private stacks not shared with other threads. These threads execute in "parallel" which is subset of concurrency.
After finishing the task they join back together and have one thread again. If need be one of these threads can fork of more threads and so on.
This process continues.
*/

#include <omp.h>
#include <stdio.h>

int main()
{
    #pragma omp parallel
    // The structure below will be parallelized
    // All variables declared in the below structure are private to each thread
    // So thread 0 will have ID as 0, thread 1 will have id 1 (private stack)
    /* All the variables defined above and outside the structure are accessible to all threads and changing them from within threads can cause race condition.
    These variables are part of heap space*/
    {
        int ID = omp_get_thread_num();
        printf("hello(%d)", ID);
        printf(" world(%d) \n", ID);
    }
}

/*
Example output of running this program
--------------------------------------
hello(10)hello(1) world(1) 
hello(5)hello(0) world(0) 
hello(2)hello(9) world(2) 
hello(6) world(9) 
hello(8) world(10) 
hello(3) world(3) 
 world(6) 
hello(7) world(7) 
hello(4) world(4) 
 world(5) 
 world(8) 
hello(11) world(11)
*/

