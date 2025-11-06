#include "EE1103lib.h"
#include <stdio.h>
#include <math.h>

float standard_deviation(float *arr, int n) // pass in the array and the length of the array to get the stdev
{   
    if (n <= 1) return 0.0f; 

    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    float mean = sum / n;

    float variance_sum = 0.0f;
    for (int i = 0; i < n; i++) {
        float diff = arr[i] - mean;
        variance_sum += diff * diff;
    }
    float variance = variance_sum / (n - 1); 

    return sqrt(variance);
}

float mean(float *arr, int n) //pass in the array and length of the array to get the mean
{
    if (n <= 0) return 0.0f;  

    float sum = 0.0f;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / n;
}

double thetatoradian(double theta) // converts theta to radian by passing in theta
{
    double radiantheta = PI / 180 *theta;
    return radiantheta;
}

double radiantotheta(double radian) // converts radian to theta by passing in radian
{
    return 180/PI *radian;
}

long long factorial(int n) // returns a long long (factorial) upon passing in the integer
{
    long long fact;
    
    if (n == 1 || n == 0)
    {
        fact = 1;
        return fact;
    }
    else 
    {
        fact = n*factorial(n-1);
        return fact;
    }
}

long double taylorsin(double theta, int N) //gives the taylor approximation of sin up to N terms by passing in the angle and N
{
    long double mysin = 0;
    for (int i = 0; i < N; i++)
    {
        mysin += (pow(-1,i) * pow(theta, (2*i)+1))/factorial((2*i)+1);
    }
    return mysin;
}

long double taylorcos(double theta, int N) //gives the taylor approximation of cos up to N terms by passing in the angle and N
{
    long double mycos = 0;
    for (int i = 0; i < N; i++)
    {
        mycos += (pow(-1,i) * pow(theta, (2*i)))/factorial((2*i));
    }
    return mycos;
}
