#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// データ数
#define N 1024

const double e = 0.0001;
const double alpha = 0.001;

struct pair {
    double x;
    double y;

} typedef pair;

double rX(double x) { return 24 * pow(x, 7) + 6 * x - 2; }

double rY(double y) { return 30 * pow(y, 5) - 4; }

double f(double x, double y) {
    return 3 * pow(x, 8) + 3 * pow(x, 2) - 2 * x + 5 * pow(y, 6) - 4 * y + 8;
}

pair steepestDescent(double x, double y) {
    pair res;
    while (fabs(rX(x)) > e || fabs(rY(y)) > e) {
        x -= alpha * rX(x);
        y -= alpha * rY(y);
    }
    res.x = x;
    res.y = y;

    return res;
}

pair recursiveDescent(pair* p, int n) {
    if (n == 1) return steepestDescent(p[0].x, p[0].y);

    pair left = recursiveDescent(p, n / 2);
    pair right = recursiveDescent(p + n / 2, n - n / 2);

    return f(left.x, left.y) < f(right.x, right.y) ? left : right;
}

int main(void) {
    pair p[N];
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        p[i].x = rand() / (1.0 + RAND_MAX) - 0.5;
        p[i].y = rand() / (1.0 + RAND_MAX) - 0.5;
    }

    pair ans = recursiveDescent(p, N);
    printf("x = %lf, y = %lf -> f(x, y) = %lf", ans.x, ans.y, f(ans.x, ans.y));
}
