#include "../general.h"

int main(int argc, char *argv[])
{
    int num_of_threads = atoi(argv[1]);

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    printf ("%s \n", "start");

    int i;
    int a[SIZE]={0}, b[SIZE]={0};

    for (i = 0; i < SIZE; i++) {
        a[i] = rand();
        // printf("%d\n", a[i]);
    }

    #pragma omp parallel for num_threads(num_of_threads) schedule(dynamic)
    for(i = 0; i < SIZE; i++) {
        b[i] = a[i];
    }

    checkCorrectness(a, b);

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 
    printf ("%s \n", "end");
    return 0;
}