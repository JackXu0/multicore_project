#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <unistd.h>
#include <sys/time.h>

#define SIZE 1000

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void allocate(int *result, int number_of_threads)
{
    for (int i = 0; i < number_of_threads; i++)
        result[i] = rand() % SIZE;

    qsort(result, number_of_threads, sizeof(int), cmpfunc);
}

int main(int argc, char *argv[])
{
    int num_of_threads = atoi(argv[1]);

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    printf("%s \n", "start");

    int i;
    int a[SIZE], b[SIZE];

    for (i = 0; i < SIZE; i++)
    {
        a[i] = rand();
        // printf("%d\n", a[i]);
    }

    int assign[num_of_threads];

    allocate(assign, num_of_threads);

    int pid, left, right;

    #pragma omp parallel num_threads(num_of_threads) private(i, pid, left, right)
    {
        pid = omp_get_thread_num();
        if (pid == 0) {
            left = 0;
            right = assign[pid];
        } else if (pid == num_of_threads - 1) {
            left = assign[pid-1];
            right = SIZE;
        } else {
            left = assign[pid-1];
            right = assign[pid];
        }
        
        for(i = left; i < right; i++) {
            b[i] = a[i];
            printf ("thread %i set %ith number in b which is %i\n", pid, i, a[i]);
        }

        printf("Thread %i duplicates %i integers\n", pid, right-left);
    }

    // for (i=0; i<SIZE; i++){
    //     printf("a[%i]=%i\tb[%i]=%i\n", i, a[i], i, b[i]);
    // }

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
    printf ("%s \n", "end");
    return 0;
}