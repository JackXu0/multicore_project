#include "../general.h"

int main(int argc, char *argv[])
{
    int num_of_threads = atoi(argv[1]);
    int size = (argc == 2)? SIZE: atoi(argv[2]);

    int a[size][size], b[size][size];

    for (int i = 0; i < size; i++) 
        for(int j = 0; j < size; j++)
            a[i][j] = rand();

    printf ("%s \n", "start");

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    #pragma omp parallel for num_threads(num_of_threads)
    for (int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            b[i][j] = a[i][j];
        }
    }

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 

    for (int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++){
            assert(b[i][j] = a[i][j]);
        }
    }

    printf ("%s \n", "end");
    return 0;
}