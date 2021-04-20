#include "../general.h"

int main(int argc, char *argv[])
{
    int num_of_threads = atoi(argv[1]);
    int size = (argc == 2)? SIZE: atoi(argv[2]);

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    printf("%s \n", "start");

    int i;
    int a[size], b[size];

    for (i = 0; i < size; i++) {
        a[i] = rand();
        // printf("%d\n", a[i]);
    }

    int assign[num_of_threads];

    allocate(assign, num_of_threads, size);

    int pid, left, right;

    #pragma omp parallel num_threads(num_of_threads) private(i, pid, left, right)
    {
        pid = omp_get_thread_num();
        left = (pid == 0)? 0: assign[pid-1];
        right = (pid == num_of_threads - 1)? size: assign[pid];
        
        for(i = left; i < right; i++) {
            b[i] = a[i];
            // printf ("thread %i set %ith number in b which is %i\n", pid, i, a[i]);
        }

        // printf("Thread %i duplicates %i integers\n", pid, right-left);
    }

    checkCorrectness(a, b, size);

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
    printf ("%s \n", "end");
    return 0;
}