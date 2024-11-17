#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        a[i] = rand();
    }
}

int upper_bound(int a[], int n, int left, int right) {
    int l = left - 1;  // 1つ前のインデックスからスタート
    int r = right;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (a[m] < n) {
            l = m;  // nより大きい要素を探す
        } else {
            r = m;
        }
    }
    return r;
}

int isSorted(int *a) {
    for (int i = 0; i < N - 1; i++) {
        if (a[i] > a[i + 1]) return 0;  // ソートされていない
    }
    return 1;  // ソートされている
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

    // 挿入ソートの実装
    for (int i = 1; i < N; i++) {
        int idx = upper_bound(a, a[i], 0, i);  // 上限を決めて挿入位置を探索
        int tmp = a[i];
        // [idx, i) の間で右にずらす
        memmove(&a[idx + 1], &a[idx], (i - idx) * sizeof(int));
        a[idx] = tmp;
    }

    t_end = clock();
    assert(isSorted(a));  // ソートされていることを確認

    printf("after sort\n");
    for (int i = 0; i < N; i++) {
        printf("%d%c", a[i], " \n"[i == N - 1]);
    }

    printf("実行時間:%f\n", (double)(t_end - t_start) / CLOCKS_PER_SEC);

    return 0;
}
