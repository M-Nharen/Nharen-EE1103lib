#include "EE1103lib.h"
#include <stdio.h>

void metropolis_sweep(int *M, int N, float J, float T) //Performs a single metropolis sweep on matrix M of size N*N at temp T
{
    for (int step = 0; step < N * N; step++) {

        // Choose a random lattice site
        int i = rand() % N;
        int j = rand() % N;

        // Compute energy change if this spin is flipped
        int s = M[i * N + j];
        float deltaE = 2.0f * J * s * neighboursum(i, j, M, N);

        // Flip spin with Metropolis acceptance criterion
        if (deltaE <= 0.0f || ((float)rand() / (float)RAND_MAX) < expf(-deltaE / T)) {
            M[i * N + j] = -s;
        }
    }
}
