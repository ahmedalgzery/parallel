#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <mpi.h>
#include <time.h>

#define ARRAY_SIZE 1000
#define GRAPH_SIZE 100

// Selection Sort
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(int arr[], int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;
        swap(&arr[min_idx], &arr[i]);
    }
}

// Parallel DFS using MPI
int adjacency_matrix[GRAPH_SIZE][GRAPH_SIZE] =
    {
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {1, 0, 0, 1},
        {0, 1, 1, 0}};

int visited[GRAPH_SIZE] = {0};

void DFS(int current_vertex)
{
    printf("Visited vertex: %d\n", current_vertex);
    visited[current_vertex] = 1;

    for (int i = 0; i < GRAPH_SIZE; i++)
    {
        if (!visited[i] && adjacency_matrix[current_vertex][i])
            DFS(i);
    }
}

int main(int argc, char *argv[])
{
    // MPI Initialization
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double start_time, end_time;

    // Selection Sort
    if (rank == 0)
    {
        int arr[ARRAY_SIZE];
        for (int i = 0; i < ARRAY_SIZE; i++)
        {
            arr[i] = rand() % 1000; // Filling the array with random values for testing
        }

        printf("Unsorted array: ");
        for (int i = 0; i < ARRAY_SIZE; i++)
            printf("%d ", arr[i]);
        printf("\n\n\n");

        start_time = clock();
        selectionSort(arr, ARRAY_SIZE);
        end_time = clock();

        printf("Sorted array: ");
        for (int i = 0; i < ARRAY_SIZE; i++)
            printf("%d ", arr[i]);
        printf("\n\n\n");

        printf("Time taken for Selection Sort: %lf seconds\n\n", (end_time - start_time) / CLOCKS_PER_SEC);
    }

    // Parallel DFS using MPI
    MPI_Barrier(MPI_COMM_WORLD); // Synchronize processes before starting DFS

    if (rank == 0)
    {
        start_time = MPI_Wtime();
    }

    int start_vertex = 0; // Starting vertex for DFS
    DFS(start_vertex);

    if (rank == 0)
    {
        end_time = MPI_Wtime();
        printf("\nTime taken for Parallel DFS using MPI: %lf seconds\n\n", end_time - start_time);
    }

    MPI_Finalize();

    return 0;
}
