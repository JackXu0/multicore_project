#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <unistd.h>
#include <sys/time.h>

void func1(int pid, int i){
    printf ("\tThread %i: start %i \n", pid, i);
    if(pid % 2 == 0) {
        float time_to_sleep = (float)(5 / (pid+1)); // sleep 5 seconds
        sleep(time_to_sleep);
        // for (int j = 0; j < 10000; ) {
        //     j++;
        //     printf("%d\n", j);
        // }

    }
    printf ("\tThread %i: end %i \n", pid, i);
}

void func2(int pid, int i){
    printf ("\tThread %i: start %i \n", pid, i);
    if(pid % 2 == 1) {
        float time_to_sleep = (float)(5 / (pid+1)); // sleep 5 seconds
        sleep(time_to_sleep);
        // for (int j = 0; j < 10000; ) {
        //     j++;
        //     printf("%d\n", j);
        // }
    }
    printf ("\tThread %i: end %i \n", pid, i);
}

int main(int argc, char *argv[])
{
    int num_of_threads = atoi(argv[1]);

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    printf ("%s \n", "start");
    int i = 0;
    int pid;

    #pragma omp parallel num_threads(num_of_threads) private(i, pid) 
    {
        pid = omp_get_thread_num();
        int thread_start_time = omp_get_wtime();
        printf ("start thread %i \n", pid);
        #pragma omp for nowait
        for (i=0; i<10; i++)
        {
            func1(pid, i);
        }
        printf ("Thread %i reach the barrier\n", pid);
        #pragma omp barrier
        #pragma omp for
        for (i=0; i<10; i++)
        {
            func2(pid, i);
        }
        printf ("end thread %i \n", omp_get_thread_num());
        printf ("!!! Thread %i's total running time: %f !!!\n", pid, omp_get_wtime() - thread_start_time);
    }

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 
    printf ("%s \n", "end");
    return 0;
}