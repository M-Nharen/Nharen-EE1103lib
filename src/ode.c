#include "EE1103lib.h"
#include <stdio.h>

// Function prototype for derivative
typedef double (*deriv_func)(double, double);

//All the functions here take input of the function, initial x0 and y0, step size, number of steps

//Euler
double euler(deriv_func f, double x0, double y0, double h, int n)
{
    double x = x0, y = y0;
    for (int i = 0; i < n; i++) {
        y += h * f(x, y);
        x += h;
    }
    return y;
}

//midpoint
double midpoint(deriv_func f, double x0, double y0, double h, int n)
{
    double x = x0, y = y0;
    for (int i = 0; i < n; i++) {
        double k1 = f(x, y);
        double k2 = f(x + h/2.0, y + (h/2.0) * k1);
        y += h * k2;
        x += h;
    }
    return y;
}

//heun
double heun(deriv_func f, double x0, double y0, double h, int n)
{
    double x = x0, y = y0;
    for (int i = 0; i < n; i++) {
        double k1 = f(x, y);
        double k2 = f(x + h, y + h * k1);
        y += (h / 2.0) * (k1 + k2);
        x += h;
    }
    return y;
}

//rk4
double rk4(deriv_func f, double x0, double y0, double h, int n)
{
    double x = x0, y = y0;
    for (int i = 0; i < n; i++) {
        double k1 = f(x, y);
        double k2 = f(x + h/2.0, y + h*k1/2.0);
        double k3 = f(x + h/2.0, y + h*k2/2.0);
        double k4 = f(x + h, y + h*k3);
        y += (h / 6.0) * (k1 + 2*k2 + 2*k3 + k4);
        x += h;
    }
    return y;
}
