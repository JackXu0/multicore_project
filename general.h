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

void allocate(int *result, int number_of_threads)
{
    for (int i = 0; i < number_of_threads; i++)
        result[i] = rand() % SIZE;

    qsort(result, number_of_threads, sizeof(int), cmpfunc);
}

void checkCorrectness(int *a, int *b) {
    for (int i=0; i<SIZE; i++)
        assert(a[i] == b[i]);
}