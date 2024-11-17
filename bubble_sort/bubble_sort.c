#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 20000

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void setup(int a[]) {
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        a[i] = rand() % N;
    }
}

int isSorted(int *a) {
    for (int i = 0; i < N - 1; i++) {
        if (a[i] > a[i + 1]) return 0;
    }
    return 1;
}

int main() {
    int a[N];
    setup(a);

    printf("before sort\n");
    for (int i = 0; i < N; i++) {
        printf("%d%c", a[i], " \n"[i == N - 1]);
    }

    clock_t t_start, t_end;
    t_start = clock();

    for (int i = 0; i < N - 1; i++) {
        for (int j = N - 1; j > i; j--) {
            if (a[i] > a[j]) swap(&a[i], &a[j]);
        }
    }

    printf("after sort\n");
    for (int i = 0; i < N; i++) {
        printf("%d%c", a[i], " \n"[i == N - 1]);
    }
    assert(isSorted(a));
    t_end = clock();
    printf("実行時間:%f\n", (double)(t_end - t_start) / CLOCKS_PER_SEC);
}
