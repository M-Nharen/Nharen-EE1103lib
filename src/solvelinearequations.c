#include "EE1103lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define zerolimit 1e-12

static void swap_rows(double** A, double* b, int i, int j, int n) {
    double tmp;
    for(int k=0; k<n; k++) {
        tmp = A[i][k];
        A[i][k] = A[j][k];
        A[j][k] = tmp;
    }
    tmp = b[i];
    b[i] = b[j];
    b[j] = tmp;
}

double *gaussian_elimination(double** A, double* b, int n) // Pass in the matrix ,vector with the constants, number of equations it will give pointer to solutions
{
    double *x = malloc(n*sizeof(double));
    for(int i=0; i<n; i++) {
        int pivot_row = i;
        double max_val = fabs(A[i][i]);
        for(int k=i+1; k<n; k++) {
            if(fabs(A[k][i]) > max_val) {
                max_val = fabs(A[k][i]);
                pivot_row = k;
            }
        }
        if(max_val < zerolimit) {
            printf("Matrix is singular or nearly singular.\n");
            exit(EXIT_FAILURE);
        }
        if(pivot_row != i)
            swap_rows(A, b, i, pivot_row, n);

        for(int k=i+1; k<n; k++) {
            double factor = A[k][i] / A[i][i];
            for(int j=i; j<n; j++)
                A[k][j] -= factor * A[i][j];
            b[k] -= factor * b[i];
        }
    }

    for(int i=n-1; i>=0; i--) {
        x[i] = b[i];
        for(int j=i+1; j<n; j++)
            x[i] -= A[i][j] * x[j];
        x[i] /= A[i][i];
    }
    return x;
}

double *lu_decomposition(double** A, double* b, int n) // Pass in the matrix ,vector with the constants, number of equations it will give pointer to solutions
{
    double *x = malloc(n*sizeof(double));
    double** L = (double**)malloc(n * sizeof(double*));
    double** U = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        L[i] = (double*)calloc(n, sizeof(double));
        U[i] = (double*)calloc(n, sizeof(double));
    }

    for (int i = 0; i < n; i++) {
        for (int k = i; k < n; k++) {
            double sum = 0.0;
            for (int j = 0; j < i; j++)
                sum += L[i][j] * U[j][k];
            U[i][k] = A[i][k] - sum;
        }

        for (int k = i; k < n; k++) {
            if (i == k)
                L[i][i] = 1.0;
            else {
                double sum = 0.0;
                for (int j = 0; j < i; j++)
                    sum += L[k][j] * U[j][i];
                if (fabs(U[i][i]) < zerolimit) {
                    printf("LU decomposition failed: zero pivot detected.\n");
                    exit(EXIT_FAILURE);
                }
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }

    double* y = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < i; j++)
            sum += L[i][j] * y[j];
        y[i] = b[i] - sum;
    }

    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++)
            sum += U[i][j] * x[j];
        if (fabs(U[i][i]) < zerolimit) {
            printf("LU decomposition failed: zero pivot during back-substitution.\n");
            exit(EXIT_FAILURE);
        }
        x[i] = (y[i] - sum) / U[i][i];
    }

    for (int i = 0; i < n; i++) {
        free(L[i]);
        free(U[i]);
    }
    free(L);
    free(U);
    free(y);
    return x;
}