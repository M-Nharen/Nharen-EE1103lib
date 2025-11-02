#include "EE1103lib.h"
#include <stdio.h>

float *newton_maker(struct point *training_data, int M)
/*Computes and returns a float array of the coefficients with the first term as the constant term and 
increasing towards the larger terms*/
{
    float *prevcol = malloc(M*(sizeof(float)));
    for (int i = 0; i < M; i++)
    {   
        prevcol[i] = training_data[i].y;
    }
    int colno = 1;
    float *outputcoeff = malloc((M)*sizeof(float));
    outputcoeff[0] = prevcol[0];
    for (int j = M-1; j > 0; j--)
    {
        float *currentcol = malloc(j*sizeof(float));
        for (int i = 0; i < j; i ++)
        {
            currentcol[i] = (prevcol[i+1] - prevcol[i])/(training_data[i+colno].x - training_data[i].x);
        }
        outputcoeff[M-j] = currentcol[0];
        colno += 1;
        free(prevcol);
        prevcol = currentcol;
    }
    free(prevcol);

    return outputcoeff;
}

float newton(int x,struct point *training_data, int M)
//returns the predicted y value of input x after curve fitting with newton's poly
{
    int *xarray = malloc(M*sizeof(int));
    xarray[0] = 1;
    float *newtonarray = newton_maker(training_data, M);
    for (int i = 1; i < M; i++)
    {
        int product = 1;
        for (int j = 0; j < i; j++)
        {
            product *= (x-training_data[j].x);
        }
        xarray[i] = product;
    }

    float returnvalue = 0;
    for (int i = 0; i < M; i++)
    {
        returnvalue += newtonarray[i]*xarray[i];
    }

    free(xarray);

    return returnvalue;
}

float lagrangian(int x, struct point *training_points, int M)
//returns predicted y value of input x after curve fitting with lagrangian poly
{
    float result = 0;
    for (int i = 0; i < M; i++)
    {
        float product=1;
        for (int j = 0; j < M; j++)
        {
            if (i != j)
            {
                product *= (float) (x-training_points[j].x)/(training_points[i].x - training_points[j].x);
            }
        }

        result += training_points[i].y*product;
    }

    return result;
}

float computepoly(int x, int n, int *arr)
//Computes value of a nth degree polynomial with coefficients in arr(a0 in arr[0])
{
    float y = 0;
    for (int i = 0; i < n+1; i++)
    {
        y += pow(x,i)*arr[i];
    }

    return y;
}
