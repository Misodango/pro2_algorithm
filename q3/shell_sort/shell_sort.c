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

// upper_bound関数の修正
int upper_bound(int a[], int n, int r) {
    int l = -1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (a[m] < n) {
            l = m; // a[m] が n より小さい場合、l を更新
        } else {
            r = m; // a[m] が n 以上の場合、r を更新
        }
    }
    return r;
}

int isSorted(int *a) {
    for (int i = 0; i < N - 1; i++) {
        if (a[i] > a[i + 1]) return 0; // ソートされていない
    }
    return 1; // ソートされている
}

// 挿入ソート
void insertionSort(int a[], int m) {
    for (int i = 1; i < m; i++) {
        int idx = upper_bound(a, a[i], i);  // バイナリサーチで挿入位置を探す
        int tmp = a[i];
        memmove(&a[idx + 1], &a[idx], (i - idx) * sizeof(int));  // 右にずらす
        a[idx] = tmp;
    }
}

// シェルソート
void shellSort(int a[], int n) {
    // シェルソートの増分列を決定
    int gap = n;
    while (gap > 0) {
        gap /= 2;
        for (int i = gap; i < N; i++) {
            // 各ギャップに対して挿入ソートを行う
            int j = i;
            int temp = a[i];
            while (j >= gap && a[j - gap] > temp) {
                a[j] = a[j - gap];
                j -= gap;
            }
            a[j] = temp;
        }
    }
}

int main() {
    int a[N];
    setup(a);

    printf("before sort\n");
    for (int i = 0; i < N; i++) {
        printf("%d%c", a[i], " \n"[i == N - 1]);
    }

    clock_t t_start, t_end;

    double bestTime = 1e9;
    int bestDivision = 2;

    // 計測して最適な分割数を決定
    for (int i = 1; i <= 10; i++) {  // nを1から10までで試す
        setup(a);
        t_start = clock();
        shellSort(a, i);  // shellSortを実行
        t_end = clock();
        double currentTime = (double)(t_end - t_start) / CLOCKS_PER_SEC;
        if (currentTime < bestTime) {
            bestTime = currentTime;
            bestDivision = i;
        }
        printf("%d:%fsec\n", i, currentTime);
    }

    t_start = clock();
    shellSort(a, bestDivision);  // 最適な分割数でソートを実行
    t_end = clock();

    assert(isSorted(a)); // ソートされていることを確認

    printf("after sort\n");
    for (int i = 0; i < N; i++) {
        printf("%d%c", a[i], " \n"[i == N - 1]);
    }

    printf("実行時間:%f, 最良分割数:%d\n",
           (double)(t_end - t_start) / CLOCKS_PER_SEC, bestDivision);

    return 0;
}
