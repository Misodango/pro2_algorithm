#include <stdio.h>

int main(void) {
    int n = 3000;
    printf("range : %d ~ %d\n", 2, n);
    int list[30001];
    for (int i = 0; i <= n; i++) {
        list[i] = i;
    }

    // 十分な大きさの配列を確保（3000までの素数は約430個）
    int primes[500];  // 余裕を持って500に
    int siz = 0;

    // エラトステネスの篩
    for (int* head = &list[2]; (*head) * (*head) <= n; head++) {
        if (*head <= 1 || *head == -1) continue;  // -1のチェックを追加
        primes[siz++] = *head;  // memmoveの代わりに直接代入

        // 倍数を消していく
        for (int i = 2; i <= n / (*head); i++) {
            list[i * (*head)] = -1;
        }
    }

    // 残りの素数を収集
    for (int i = 2; i <= n; i++) {
        if (list[i] != -1 && i > primes[siz-1]) {
            primes[siz++] = i;  // memmoveの代わりに直接代入
        }
    }

    printf("%d found\n", siz);
    for (int i = 0; i < siz; i++) {
        printf("%d ", primes[i]);
    }
    puts("");

    return 0;
}
