#ifndef EE1103LIB_H
#define EE1103LIB_H

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define PI 3.1415

typedef double (*deriv_func)(double, double);

struct point
{
    int x;
    float y;
};

typedef struct {
    int index;
    double x;
    
    double y;
} Peak;

double randombetween(double start, double end, const char *type);
/*Gives random value between start and end(inclusive) of the type integer or float
Write the type as 'int' or 'float' inside quotes*/
float* randarray(long size, int start, int end);
//returns a float array with some particular startpoint endpoint and size
float* normal(long size, float mean, float stdev);
//Gives a normal distribution of given size,mean and stdev
float standard_deviation(float *arr, int n);
//Finds the standard deviation of array of length n
float mean(float *arr, int n);
//Finds mean of array of length n
float ttest(float *arr1, float *arr2, int n1, int n2);
//Enter the 2 normal distributions and their sizes
double radiantotheta(double radian);
//converts radian to theta
double thetatoradian(double theta);
//converts theta to radian
long long factorial(int n);
//finds factorial
long double taylorcos(double theta, int N);
//Finds the taylor expansion of cos upto N terms
long double taylorsin(double theta, int N);
//Finds the taylor expansion of sin upto N terms
int **emptymatrix(int N);
//creates an empty matrix of size N*N
void freematrix(int**matrix, int N);
//frees a matrix of size N*N
int neighboursum(int *M, int i, int j, int N);
//It finds the sum of the values in the neighbour of the point i,j in a matrix M of size N*N(edge points have wrap around)
void matrixfillrandvalues(int **M, int N, int start, int end);
//Fills random values in a matrix
void metropolis_sweep(int *M, int N, float J, float T);\
//Does one metropolis-hastings sweep on a matrix M of size N*N at temperature T and coeff J 
float computepoly(int x, int n, int *arr);
//Computes the value of a polynomial of order n at x. The coefficients of the polynomial are the values in the array (a0 in arr[0])
float lagrangian(int x, struct point *training_points, int M);
// Gives the lagrangian prediction of the y coordinate of point x given a set of M input training points 
float newton(int x,struct point *training_data, int M);
// Gives the newton polynomial prediction of the y coordinate of point x given a set of M input training points 
float *newton_maker(struct point *training_data, int M);
/* Gives the coefficients of the newton polynomial predicted as a float array of the coefficients with the first term as the constant term(x^0) and 
increasing towards the larger terms*/
double euler(deriv_func f, double x0, double y0, double h, int n);
/*The four following functions euler, midpoint, heun,rk4 give the value of xn,yn (the value of x,y after n steps of length h)
when the value of initial coordinates n and step size is passed in along with the derivative function
ex: 
double f(double t, double y)
{
    return -2.0 * y + 1.0; // example ODE: dy/dt = -2y + 1
} 
yn = euler(f,t0,y0,h,n)*/
double midpoint(deriv_func f, double x0, double y0, double h, int n);
double heun(deriv_func f, double x0, double y0, double h, int n);
double rk4(deriv_func f, double x0, double y0, double h, int n);
int findpeaks(FILE *input);
/*Given a file pointer input, findpeaks finds the location of the peaks, width of the peaks, separation between peaks and outputs them*/
double *lu_decomposition(double** A, double* b, int n);
/*outputs a double pointer pointing to the solutions of the set of n linear equations whose coefficients are stored in A and its 
constants are stored in array b by LU Decomposition. Remember to free the solution marix that is returned*/
double *gaussian_elimination(double** A, double* b, int n);
/*outputs a double pointer pointing to the solutions of the set of n linear equations whose coefficients are stored in A and its 
constants are stored in array b by gaussian elimination. Remember to free the solution marix that is returned*/
int hamming(unsigned char* a, unsigned char* b, int N);
//perform bitwise hamming on 2 N sized bits
void add_noise(unsigned char *block, int N, double p);
//adds noise to a block of size N flipping with probability p
void insert_bits(unsigned char *dest, unsigned char *src, int d, int M);
// Inserts M bits from src[] into dest[] starting at bit offset d
unsigned char *generate_random_bits(int N);
// returns a char * pointer with randomly generated bits
float gaussian_noise(float stddev);
// gives out a single value of guassian noise with the whole having standard deviation as stddev

#endif