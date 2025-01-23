#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * 焼きなましでヒューリスティックに解くのずるいかもしれん
 *
 * 発展課題の方で出したのを，焼きなましでやる
 * 開始地点を3点にランダムにとって，alphaで焼く
 *
 */

#define N 9
#define MAX_ITER 1000

const double e = 0.00001;
const double init_temp = 0.01;
const double cooling = 0.995;

double f(double x) {
    return 3 * pow(x, 8.0) + 5 * pow(x, 6.0) + 7 * pow(x, 3.0) + 5;
}

double df(double x) {
    return 24 * pow(x, 7.0) + 30 * pow(x, 5.0) + 21 * pow(x, 2.0);
}

double steepestDescent(double x, double temp) {
    int iter = 0;
    while (fabs(df(x)) > e && iter < MAX_ITER) {
        x -= temp * df(x);
        temp *= cooling;
        iter++;
    }
    return x;
}

double descentAll(double x[], int n) {
    double minFx = 1e9;
    double res = x[0];
    for (int i = 0; i < n; i++) {
        x[i] = steepestDescent(x[i], init_temp);
        if (minFx > f(x[i])) {
            res = x[i];
            minFx = f(x[i]);
        }
    }
    return res;
}

int main(void) {
    double x[N];
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        x[i] = rand() / (1.0 + RAND_MAX) - 0.5;
    }

    double y[3];
    y[0] = descentAll(x, 3);
    y[1] = descentAll(&x[3], 3);
    y[2] = descentAll(&x[6], 3);

    double ans = descentAll(y, 3);
    printf("x = %lf -> f(x) = %lf\n", ans, f(ans));
}
