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

void checkCorrectness(int *a, int *b, int size) {
    for (int i=0; i<size; i++)
        assert(a[i] == b[i]);
}

void fibo(int n) {
    int t1 = 0, t2 = 1;
    int nextTerm;

    for (int i = 1; i <= n; ++i) {
        // printf("%d, ", t1);
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
    }

}