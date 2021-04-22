#include "../general.h"

int main(int argc, char *argv[])
{
    int num_of_threads = atoi(argv[1]);
    int size = (argc == 2)? SIZE: atoi(argv[2]);

    int batch = size / num_of_threads;
    int mod = size % num_of_threads;

    int left[num_of_threads];
    int right[num_of_threads];

    for (int j = 0, temp = 0; j < num_of_threads; j++) {
        left[j] = temp;
        temp = (j < mod)? temp + batch + 1: temp + batch;
        right[j] = temp;
    }

    printf ("%s \n", "Bottleneck 1 start");

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    #pragma omp parallel num_threads(num_of_threads) shared(left, right)
    {
        int pid = omp_get_thread_num();
        for(int i = left[pid], count = 0; i < right[pid]; i++, count++) {
            
            fibo(i % 1000);
            # pragma omp barrier
            
        }
    }

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    printf ("%s \n", "Bottleneck 2 start");

    gettimeofday(&start, NULL);

    #pragma omp parallel num_threads(num_of_threads)
    {
        int pid = omp_get_thread_num();
        for(int i = left[pid]; i < right[pid];) {
            #pragma omp critical
            {
                fibo(i % 1000);
                i++;
            }
        }
    }
    
    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 

    printf ("%s \n", "Bottleneck 3 start");

    gettimeofday(&start, NULL);

    #pragma omp parallel num_threads(num_of_threads)
    {
        #pragma omp for ordered
        for(int i = 0; i<size; i++) 
        {
            #pragma omp ordered
            {
                fibo(i % 1000);
            }
        }
    }

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 

    int assign[num_of_threads];

    allocate(assign, num_of_threads, size);

    for (int j = 0; j < num_of_threads; j++) {
        left[j] = (j == 0)? 0: assign[j-1];
        right[j] = (j == num_of_threads - 1)? size: assign[j];
    }

    printf ("%s \n", "Bottleneck 4 start");

    gettimeofday(&start, NULL);

    #pragma omp parallel num_threads(num_of_threads)
    {
        int pid = omp_get_thread_num();
        for(int i = left[pid]; i < right[pid]; i++) {
            fibo(i % 1000);
        }
        # pragma omp barrier
    }

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);

    printf ("%s \n", "Bottleneck 5 start");

    gettimeofday(&start, NULL);

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

    // checkCorrectness(a, b, size);

    printf ("%s \n", "end");
    return 0;
}