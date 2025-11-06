#include "EE1103lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int **emptymatrix(int N) //outputs the pointer to an empty matrix of size N
{
    int **matrix = malloc(N*sizeof(int*));

    for (int i = 0; i < N; i++)
    {
        matrix[i] = malloc(N*sizeof(int));
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = 0;
        }
    }

    return matrix;
}

void freematrix(int**matrix, int N) //frees the matrix given input pointer to matrix, size N*N
{
    for (int i = 0; i < N; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

int neighboursum(int *M, int i, int j, int N) //finds the sum of the values of its neighbours(wrap around is considered)
{
    int up = M[((i - 1 + N) % N) * N + j];
    int down = M[((i + 1) % N) * N + j];
    int left = M[i * N + (j - 1 + N) % N];
    int right = M[i * N + (j + 1) % N];
    return (up + down + left + right);
}

void matrixfillrandvalues(int **M, int N, int start, int end)
{
    for (int i = 0; i<N; i++)
    {
        for (int j = 0; j<N; j++)
        {
            M[i][j] = randombetween(start, end, "int");
        }
    }
}