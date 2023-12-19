#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdint.h>

#define SIZE 100000000
#define NUM_THREADS 2

double array[SIZE];

void *sequentialSum(void *arg)
{
    double sum = 0.0;
    for (int i = 0; i < SIZE; i++)
    {
        sum += array[i];
    }
    pthread_exit((void *)(intptr_t)sum);
}

void *parallelSum(void *arg)
{
    int thread_id = *((int *)arg);
    int chunk_size = SIZE / NUM_THREADS;
    int start = thread_id * chunk_size;
    int end = (thread_id == NUM_THREADS - 1) ? SIZE : start + chunk_size;

    double local_sum = 0.0;
    for (int i = start; i < end; i++)
    {
        local_sum += array[i];
    }

    pthread_exit((void *)(intptr_t)local_sum);
}

int main()
{
    // Initialize array with some values
    for (int i = 0; i < SIZE; i++)
    {
        array[i] = i + 1;
    }

    pthread_t threads[NUM_THREADS];
    struct timeval start, end;

    // Sequential Sum
    gettimeofday(&start, NULL);
    double sequential_result = 0.0;
    pthread_create(&threads[0], NULL, sequentialSum, NULL);
    pthread_join(threads[0], (void **)&sequential_result);
    gettimeofday(&end, NULL);

    printf("Sequential Sum: %f\n", sequential_result);
    printf("Sequential Time: %ld microseconds\n", (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));

    // Parallel Sum
    gettimeofday(&start, NULL);
    double parallel_results[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++)
    {
        int *thread_id = malloc(sizeof(int));
        *thread_id = i;
        pthread_create(&threads[i], NULL, parallelSum, (void *)thread_id);
    }
    double parallel_sum = 0.0;
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], (void **)&parallel_results[i]);
        parallel_sum += (double)(intptr_t)parallel_results[i];
    }
    gettimeofday(&end, NULL);

    printf("Parallel Sum: %f\n", parallel_sum);
    printf("Parallel Time: %ld microseconds\n", (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec));

    return 0;
}
