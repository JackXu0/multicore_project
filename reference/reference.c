#include "../general.h"

int main(int argc, char *argv[])
{
    int num_of_threads = atoi(argv[1]);
    int size = (argc == 2)? SIZE: atoi(argv[2]);
    int i;

    // int a[size], b[size];

    // for (int i = 0; i < size; i++) {
    //     a[i] = rand();
    // }

    int batch = size / num_of_threads;
    int mod = size % num_of_threads;

    int left[num_of_threads];
    int right[num_of_threads];

    for (int j = 0, temp = 0; j < num_of_threads; j++) {
        left[j] = temp;
        temp = (j < mod)? temp + batch + 1: temp + batch;
        right[j] = temp;
    }

    printf ("%s \n", "start");

    omp_set_num_threads(num_of_threads);

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    // #pragma omp parallel default(none) private(i) shared(a, b, size)
    // {
    //     #pragma omp for
    //     for (i = 0; i < size; i++) {
    //         // b[i] = a[i];
    //         fibo(i % 1000);
    //         // printf ("set %ith number in b which is %i\n", i, a[i]);
    //     }
    // }

    #pragma omp parallel num_threads(num_of_threads)
    {
        int pid = omp_get_thread_num();
        int i;
        for(i = left[pid]; i < right[pid]; i++) {
            fibo(i % 1000);
        }
    }

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 

    checkCorrectness(a, b, size);

    printf ("%s \n", "end");
    return 0;
}