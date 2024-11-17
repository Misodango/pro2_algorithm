#include <stdio.h>

double y(double u) {
    double v = 1000.0 / 36.0;
    double g = 9.8;
    return 0.75 * v + (v * v / (2 * u * g));
}

double binary_search(double n) {
    double l = 0.1;
    double r = 1.0;
    double e = 0.01;
    // int r = N;
    while (r - l >= e) {
        double m = (l + r) / 2;
        if (y(m) < 100)
            r = m;
        else
            l = m;
    }
    return l;
}

int main(void) {
    double u = binary_search(100.0);
    printf("%lf\n", u);
}
