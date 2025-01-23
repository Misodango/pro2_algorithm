#include <stdio.h>

/*
 * 小文字大文字の連続する文字列を暗号化するときには使いやすい
 * 2023年度の過去問用
 */

// index[c] := cに対応する表の番号
// dict[n] := nに対応する文字

int idx[1024];
char dict[1024];

void encode(char str[], int n, int m) {
    for (int i = 0; i < 100 && str[i]; i++) {
        char c = str[i];
        int id = idx[c];
        if (!id) {
            printf("%c", c);
            continue;
        }
        int y = id / 7, x = id % 7;
        y = (y + n) % 8;
        x = (x + m) % 7;
        int newId = y * 7 + x;
        printf("%c", dict[newId]);
    }
    puts("");
}

int main() {
    for (int i = 0; i < 27; i++) {
        int y = i % 4, x = i / 4;
        // 2行目までと78行目以降は小文字
        if (2 <= y && y <= 3) {
            y += 4;
        }
        idx[i + 'a'] = y * 7 + x;
        dict[y * 7 + x] = i + 'a';
    }

    for (int i = 0; i < 27; i++) {
        // printf("%d %d\n", i % 4, i / 4);
        int y = i % 4, x = i / 4;
        // 2行目までと78行目以降は小文字
        if (y < 2) {
            y += 4;
        }
        idx[i + 'A'] = y * 7 + x;
        dict[y * 7 + x] = i + 'A';
    }

    idx['!'] = 20;
    idx['?'] = 27;
    idx[','] = 48;
    idx['.'] = 55;
    dict[20] = '!';
    dict[27] = '?';
    dict[48] = ',';
    dict[55] = '.';

    for (int i = 0; i < 56; i++) {
        printf("%c%c", dict[i], " \n"[i % 7 == 6]);
    }

    char str[100] = ". WTIX Ab UT?!?Av frbEXO\n";
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 7; j++) {
            encode(str, i, j);
            char tmp;
            if (scanf("%c", &tmp))
                ;
        }
    }

    return 0;
}
