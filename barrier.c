#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
    int num_of_threads = atoi(argv[1]);

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    printf ("%s \n", "start");
    int i = 0;
    # pragma omp parallel num_threads(num_of_threads) private(i) 
    {
        printf ("start thread %i \n", omp_get_thread_num());
        #pragma omp for nowait
        for (i=0; i<10; i++)
        {
            printf ("start %i \n", i);
            if(i == 0){
                unsigned int time_to_sleep = 2; 
                while(time_to_sleep)
                    time_to_sleep = sleep(time_to_sleep);
            }
            printf ("end %i \n", i);
        }
        // #pragma omp barrier
        #pragma omp for nowait
        for (i=0; i<10; i++)
        {
            printf ("start %i \n", i);
            if(i == 9){
                unsigned int time_to_sleep = 1; // sleep 10 seconds
                while(time_to_sleep)
                    time_to_sleep = sleep(time_to_sleep);
            }
            printf ("end %i \n", i);
        }
        printf ("end thread %i \n", omp_get_thread_num());
    }

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 
    printf ("%s \n", "end");
    return 0;
}
