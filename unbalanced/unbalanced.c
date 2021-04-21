#include "../general.h"

int main(int argc, char *argv[])
{
    int num_of_threads = atoi(argv[1]);
    int size = (argc == 2)? SIZE: atoi(argv[2]);

    int a[size], b[size];

    for (int i = 0; i < size; i++) {
        a[i] = rand();
    }

    int assign[num_of_threads];

    allocate(assign, num_of_threads, size);

    int left[num_of_threads];
    int right[num_of_threads];

    for (int j = 0; j < num_of_threads; j++) {
        
        left[j] = (j == 0)? 0: assign[j-1];
        right[j] = (j == num_of_threads - 1)? size: assign[j];
    }
    
    printf("%s \n", "start");

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    #pragma omp parallel num_threads(num_of_threads)
    {
        int pid = omp_get_thread_num();
        for(int i = left[pid]; i < right[pid]; i++) {
            b[i] = a[i];
            printf ("thread %i set %ith number in b which is %i\n", pid, i, a[i]);
        }

        // printf("Thread %i duplicates %i integers\n", pid, right-left);
    }

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    checkCorrectness(a, b, size);

    printf ("%s \n", "end");
    return 0;
}