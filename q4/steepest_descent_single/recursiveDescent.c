#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1024

const double e = 0.0001;
const double alpha = 0.001;

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

double recursiveDescent(double x[], int n) {
    if (n == 1) return steepestDescent(x[0]);

    double left = recursiveDescent(x, n / 2);
    double right = recursiveDescent(x + n / 2, n - n / 2);

    return f(left) < f(right) ? left : right;
}

int main(void) {
    double x[N];
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        x[i] = rand() / (1.0 + RAND_MAX) - 0.5;
    }

    double ans = recursiveDescent(x, N);
    printf("x = %lf -> f(x) = %lf\n", ans, f(ans));
}
