#include "../general.h"

int main(int argc, char *argv[])
{
    int num_of_threads = atoi(argv[1]);
    int size = (argc == 2)? SIZE: atoi(argv[2]);

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    printf ("%s \n", "start");

    int i;
    int a[size], b[size];

    for (i = 0; i < size; i++) {
        a[i] = rand();
        // printf("%d\n", a[i]);
    }

    #pragma omp parallel num_threads(num_of_threads) private(i) shared(a,b)
    {
        int pid = omp_get_thread_num();
        int batch = size / num_of_threads;
        int start = pid * batch;
        int end = (pid+1) * batch;
        for(i = start; i < end;) {
            #pragma omp critical
            {
                // printf("thread %i has entered the critical region\n", pid);
                b[i] = a[i];
                i++;
                // printf ("thread %i set %ith number in b which is %i\n", pid, i, a[i]);
            }
        }
    }

    checkCorrectness(a, b, size);

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 
    printf ("%s \n", "end");
    return 0;
}