#include <math.h>
#include <stdio.h>

const double e = 0.0001;
const double alpha = 0.0001;

double f(double x) {
    return 3 * pow(x, 8.0) + 5 * pow(x, 6.0) + 7 * pow(x, 3.0) + 5;
}

double df(double x) {
    return 24 * pow(x, 7.0) + 30 * pow(x, 5.0) + 21 * pow(x, 2.0);
}

double steepestDescent(double x) {
    while (fabs(df(x)) > e) {
        x -= alpha * df(x);
    }
    return x;
}
int main(void) {
    double x = -1;
    x = steepestDescent(x);
    printf("x = %lf -> f(x) = %lf", x, f(x));
}
