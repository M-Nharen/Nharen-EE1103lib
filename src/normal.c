#include "EE1103lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float* normal(long size, float mean, float stdev)
{
    float *ptr1 = randarray(size,0,1);
    float *ptr2 = randarray(size,0,1);
    float *ptr = (float*) malloc(size * sizeof(float));
    
    for (int i = 0; i < size; i++)
    {
        ptr[i] = pow((-2*log(ptr1[i])),0.5) * cos(2 * PI * ptr2[i])*stdev + mean;
    } 

    free(ptr1);
    free(ptr2);
    return ptr;
}

#include "EE1103lib.h"
#include <math.h>

float ttest(float *arr1, float *arr2, int n1, int n2) //Enter the 2 normal distributions and their sizes
{
    float mean1 = mean(arr1, n1);
    float mean2 = mean(arr2, n2);

    float stdv1 = standard_deviation(arr1, n1);
    float stdv2 = standard_deviation(arr2, n2);

    float numerator = mean1 - mean2;
    float denominator = sqrtf((stdv1 * stdv1 / n1) + (stdv2 * stdv2 / n2));

    if (denominator == 0.0f) {
        fprintf(stderr, "Error: zero denominator in t-test (likely identical data)\n");
        return 0.0f;
    }

    return numerator / denominator;
}
