#include "../general.h"

int main(int argc, char *argv[])
{
    int num_of_threads = atoi(argv[1]);
    int size = (argc == 2)? SIZE: atoi(argv[2]);

    // int a[size], b[size];

    // for (int i = 0; i < size; i++) {
    //     a[i] = rand();
    // }

    // int batch = size / num_of_threads;
    // int mod = size % num_of_threads;

    int left[num_of_threads];
    int right[num_of_threads];

    for (int j = 0, temp = 0; j < num_of_threads; j++) {
        left[j] = temp;
        temp = (j < mod)? temp + batch + 1: temp + batch;
        right[j] = temp;
    }

    printf ("%s \n", "start");

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    #pragma omp parallel num_threads(num_of_threads) shared(left, right)
    {
        int pid = omp_get_thread_num();
        for(int i = left[pid], count = 0; i < right[pid]; i++, count++) {
            
            // b[i] = a[i];
            fibo(i % 1000);
            // if(count < batch) {
                // printf("thread %i has reached the barrier\n", pid);
                # pragma omp barrier
            // }
            
        }
    }

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 

    // checkCorrectness(a, b, size);

    printf ("%s \n", "end");
    return 0;
}