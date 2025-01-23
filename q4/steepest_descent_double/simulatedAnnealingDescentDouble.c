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

pair simulatedAnnealingDescent(double x, double y, double maxTime) {
    clock_t start = clock();
    double temp = 1.0;
    double cooling = 0.95;

    while (temp > e && (double)(clock() - start) / CLOCKS_PER_SEC < maxTime) {
        x -= temp * rX(x);
        y -= temp * rY(y);
        temp *= cooling;
    }

    pair res = {x, y};
    return res;
}

pair recursiveSimulatedAnnealing(pair* p, int n, double maxTime) {
    if (n == 1) {
        pair res = simulatedAnnealingDescent(p[0].x, p[0].y, maxTime);
        return res;
    }

    pair left = recursiveSimulatedAnnealing(p, n / 2, maxTime);
    pair right = recursiveSimulatedAnnealing(p + n / 2, n - n / 2, maxTime);

    return f(left.x, left.y) < f(right.x, right.y) ? left : right;
}

int main(void) {
    pair p[N];
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        p[i].x = rand() / (1.0 + RAND_MAX) - 0.5;
        p[i].y = rand() / (1.0 + RAND_MAX) - 0.5;
    }

    pair ans = recursiveSimulatedAnnealing(p, N, 10.0);  // maxTimeを追加
    printf("x = %lf, y = %lf -> f(x, y) = %lf\n", ans.x, ans.y,
           f(ans.x, ans.y));
}
