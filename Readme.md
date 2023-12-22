# Parallel Algorithms with MPI

This C code showcases the implementation of two parallel algorithms: Selection Sort and Parallel Depth-First Search (DFS) using the Message Passing Interface (MPI). The code is designed to be executed in a parallel computing environment, leveraging MPI to distribute tasks among multiple processes.

## Selection Sort

The code begins by implementing the Selection Sort algorithm, a straightforward comparison-based sorting algorithm. The main process (rank 0) generates a random array, prints the unsorted array, performs the selection sort in parallel using multiple MPI processes, and then prints the sorted array along with the time taken for the sorting process.

## Parallel DFS using MPI

Following the Selection Sort section, the code presents a parallel implementation of Depth-First Search (DFS) using MPI. It uses an adjacency matrix to represent a graph and employs MPI processes to traverse the graph in parallel. The DFS algorithm starts from a specified vertex (in this case, vertex 0), and each process explores a subset of the vertices. The visited vertices are printed, and the time taken for the entire DFS process is displayed by the main process.

## Usage

To compile and execute the code, you'll need to have MPI installed on your system. Use a command like the following:

```bash
mpicc -o parallel_algorithm parallel_algorithm.c -lm -lpthread
mpirun -np <number_of_processes> ./parallel_algorithm
```

## Notes

- Ensure that MPI is correctly installed on your system before compiling and running the code.
- The code assumes a fixed-size graph (GRAPH_SIZE) and array (ARRAY_SIZE) for simplicity. Modify these constants as needed for your specific use case.
- The code uses random values for the array to demonstrate the sorting algorithm. You may replace this with your own dataset.
- Pay attention to the MPI functions used for timing (MPI_Wtime) and synchronization (MPI_Barrier).
