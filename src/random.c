#include "EE1103lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

double randombetween(double start, double end, const char *type) //Gives random value between start and end(inclusive) of the type integer or float
//Write the type as 'int' or 'float' inside quotes
{ 
    if (start > end) {          //Protects against accidental input order mistake in case someone enters end and then start
        double tmp = start;
        start = end;
        end = tmp;
    }

    if (strcmp(type, "int") == 0) {
        int s = (int)start;
        int e = (int)end;
        return (rand() % (e - s + 1)) + s;
    } else if (strcmp(type, "float") == 0) {
        double scale = rand() / (double)RAND_MAX;
        return start + scale * (end - start);
    } else {
        fprintf(stderr, "Invalid type: must be \"int\" or \"float\"\n");
        exit(EXIT_FAILURE);
    }
}

float* randarray(long size, int start, int end) //returns a float array with some particular startpoint endpoint and size
{

    float *ptr = (float*) malloc(size * sizeof(float));

    for (int i = 0; i < size; i++)
    {
        ptr[i] = randombetween(start, end, "float");
    }

    return ptr;
}

float gaussian_noise(float stddev) // gives out a single value of guassian noise with the whole having standard deviation as stddev
{
    float u1 = (rand() + 1.0) / (RAND_MAX + 1.0);
    float u2 = (rand() + 1.0) / (RAND_MAX + 1.0);
    float z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * PI * u2);
    return z0 * stddev;
}