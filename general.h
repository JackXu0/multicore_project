#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <unistd.h>
#include <sys/time.h>
#include <assert.h>

#define SIZE 100000

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void allocate(int *result, int number_of_threads, int size)
{
    for (int i = 0; i < number_of_threads; i++)
        result[i] = rand() % size;

    qsort(result, number_of_threads, sizeof(int), cmpfunc);
}

void allocate2(int *result, int number_of_threads, int size)
{
    if(number_of_threads == 1){
        result[0] = size;
        return;
    }

    result[0] = size/2;
    for (int i = 0; i < number_of_threads; i++)
        result[i] = size/(2*number_of_threads-2);

    // qsort(result, number_of_threads, sizeof(int), cmpfunc);
}

void checkCorrectness(int *a, int *b, int size) {
    for (int i=0; i<size; i++)
        assert(a[i] == b[i]);
}