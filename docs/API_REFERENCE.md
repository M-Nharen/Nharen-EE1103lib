Nharen-EE1103lib — API Reference

Comprehensive reference for all public functions in the EE1103lib C library.
Each function is declared in include/EE1103lib.h and implemented in the corresponding .c file under src/.

🧩 Contents

- [Random & Noise Functions](#-random--noise-functions)
- [Statistical Utilities](#-statistical-utilities)
- [Trigonometric & Series Functions](#-trigonometric--series-functions)
- [Matrix Utilities](#-matrix-utilities)
- [Interpolation](#-interpolation)
- [Ordinary Differential Equation (ODE) Solvers](#-ordinary-differential-equation-ode-solvers)
- [Linear Algebra Solvers](#-linear-algebra-solvers)
- [Signal Analysis](#-signal-analysis)
- [Monte Carlo Simulation](#-monte-carlo-simulation)
- [Bitwise & Noise Operations](#-bitwise--noise-operations)
- [Data Structures](#-data-structures)
- [Memory Management Notes](#-memory-management-notes)
- [Example — Using the Library](#-example--using-the-library)

🎲 Random & Noise Functions
```
double randombetween(double start, double end, const char *type)

Returns a random number between start and end (inclusive).

Parameters

start, end — range of values

type — "int" or "float"

Returns
A random integer or float.

Example

double x = randombetween(0, 1, "float");
```
```
float* randarray(long size, int start, int end)

Generates an array of uniformly distributed floats in [start, end).

Returns
Pointer to dynamically allocated array (caller must free() it).

Example

float *arr = randarray(10, 0, 5);
...
free(arr);
```
```
float gaussian_noise(float stddev)

Generates a single Gaussian-distributed random value with standard deviation stddev.
```
📊 Statistical Utilities
```
float mean(float *arr, int n)

Computes the arithmetic mean of an array.

Returns
Mean value (0 if n <= 0).
```
```
float standard_deviation(float *arr, int n)

Computes the sample standard deviation of an array.

Returns
Sample standard deviation (0 if n <= 1).
```
```
float* normal(long size, float mean, float stdev)

Generates an array of normally distributed random numbers using the Box–Muller transform.

Returns
Pointer to dynamically allocated array.
```
```
float ttest(float *arr1, float *arr2, int n1, int n2)

Performs an unpaired Student’s t-test between two samples.

Returns
t-statistic value.
```
🧮 Trigonometric & Series Functions
```
double thetatoradian(double theta)

Converts degrees to radians.
```
```
double radiantotheta(double radian)

Converts radians to degrees.
```
```
long long factorial(int n)

Computes factorial recursively.
Use with care for large n (overflow possible).
```
```
long double taylorsin(double theta, int N)

Approximates sin(theta) using N-term Taylor expansion.
```
```
long double taylorcos(double theta, int N)

Approximates cos(theta) using N-term Taylor expansion.
```
🧱 Matrix Utilities
```
int** emptymatrix(int N)

Allocates an N×N integer matrix initialized to zero.

Returns
Pointer to dynamically allocated 2D matrix.
```
```
void freematrix(int **matrix, int N)

Frees memory for a matrix allocated with emptymatrix().
```
```
int neighboursum(int *M, int i, int j, int N)

Returns sum of 4-connected neighbors (up, down, left, right) of (i, j)
in a flattened N×N matrix, using wrap-around edges.
```
```
void matrixfillrandvalues(int **M, int N, int start, int end)

Fills matrix with random integer values in [start, end].
```

📈 Interpolation
```
float lagrangian(int x, struct point *training_points, int M)

Predicts y using Lagrange interpolation over M data points.
```
```
float newton(int x, struct point *training_data, int M)

Predicts y using Newton’s divided difference polynomial.
```
```
float* newton_maker(struct point *training_data, int M)

Generates and returns coefficient array of the Newton polynomial.
The array is ordered by increasing power of x (constant term first).
```
```
float computepoly(int x, int n, int *arr)

Evaluates a polynomial of degree n at x
where arr[i] is coefficient of x^i.
```
📘 Ordinary Differential Equation (ODE) Solvers

All solvers take:

f — derivative function double f(double x, double y)

x0, y0 — initial conditions

h — step size

n — number of steps

They return the final value of y after n steps.
```
double euler(deriv_func f, double x0, double y0, double h, int n)

Classical explicit Euler method.

double midpoint(deriv_func f, double x0, double y0, double h, int n)

2nd-order midpoint method.

double heun(deriv_func f, double x0, double y0, double h, int n)

Heun’s improved Euler method.

double rk4(deriv_func f, double x0, double y0, double h, int n)

4th-order Runge–Kutta method.
```

🔢 Linear Algebra Solvers
```
double* gaussian_elimination(double** A, double* b, int n)

Solves the linear system A·x = b using Gaussian elimination
with partial pivoting.

Returns
Pointer to solution vector (double*), must free() after use.
```
```
double* lu_decomposition(double** A, double* b, int n)

Solves A·x = b using LU decomposition and back-substitution.

Returns
Pointer to solution vector (double*), must free().
```
📉 Signal Analysis
```
int findpeaks(FILE *input)

Reads a CSV file (x,y pairs) and prints detected peak locations, widths, and separations.

Algorithm steps

Smooths signal with moving average

Removes outliers

Computes dynamic threshold (mean + k·σ)

Detects peaks

Filters by minimum separation

Prints a formatted results table
```

🔥 Monte Carlo Simulation
```
void metropolis_sweep(int *M, int N, float J, float T)

Performs one Metropolis–Hastings sweep on an N×N spin lattice.

Parameters

M — integer lattice (±1 values)

N — lattice size

J — coupling constant

T — temperature
```
⚙️ Bitwise & Noise Operations
```
int hamming(unsigned char* a, unsigned char* b, int N)

Computes the bitwise Hamming distance between two bit arrays of length N.
```
```
void add_noise(unsigned char *block, int N, double p)

Flips each bit in block with probability p.
```
```
void insert_bits(unsigned char *dest, unsigned char *src, int d, int M)

Inserts M bits from src into dest, starting at bit offset d.
```
```
unsigned char* generate_random_bits(int N)

Generates a random bit sequence of length N bits.
Returns a dynamically allocated buffer (caller frees it).
```
🧱 Data Structures
```
struct point

Represents an (x, y) data pair for interpolation.

struct point {
    int x;
    float y;
};
```
```
typedef struct { int index; double x; double y; } Peak;

Stores peak index, x-coordinate, and height (used in findpeaks).
```
```
typedef double (*deriv_func)(double, double)

Function pointer type for derivative functions in ODE solvers.
```

🧩 Memory Management Notes

Functions returning arrays or pointers (e.g. randarray, newton_maker, normal, gaussian_elimination) allocate memory dynamically.
Always free() them after use.

Matrix utilities (emptymatrix, freematrix) allocate and deallocate 2D integer matrices safely.

Functions that return scalars (like rk4, mean, taylorsin) require no memory cleanup.

🧰 Example — Using the Library
```
#include "EE1103lib.h"
#include <stdio.h>

double dydx(double x, double y) { return -2*y + 1; }

int main() {
    double y = rk4(dydx, 0.0, 1.0, 0.1, 10);
    printf("RK4 result = %.6f\n", y);

    float arr[5] = {1,2,3,4,5};
    printf("Mean = %.2f, SD = %.2f\n", mean(arr,5), standard_deviation(arr,5));

    return 0;
}
```


Compile with:

gcc main.c -I include libee1103.a -lm -o main

📜 License

MIT License — see LICENSE
