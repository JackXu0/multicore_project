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

    // unsigned int time_to_sleep = 10; // sleep 10 seconds
    // while(time_to_sleep)
    //     time_to_sleep = sleep(time_to_sleep);
    int i;

    #pragma omp parallel for num_threads(num_of_threads)
    for(i = 0; i < 10; i++){
        int thread_num = omp_get_thread_num();
        if(i < 2){
            unsigned int time_to_sleep = 1; // sleep 10 seconds
            while(time_to_sleep)
                time_to_sleep = sleep(time_to_sleep);
            printf ("Hello from %i \n", thread_num);
        }else{
            printf ("Hello from %i \n", thread_num);
        }
        
    }

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 

    printf ("%s \n", "end");
    return 0;
}