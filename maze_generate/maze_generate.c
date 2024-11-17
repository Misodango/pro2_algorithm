#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define max_x 10000
#define max_y 10000

int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
int field[max_y][max_x];

int isValidWall(int y, int x) {
    if (y < 0 || y >= max_y || x < 0 || x >= max_x) return 0;
    if (field[y][x] == 0) {
        return 1;
    } else {
        return 0;
    }
}

int createWall(int y, int x) {
    int randint = rand() % 4;
    int nx = x + dx[randint], ny = y + dy[randint];
    if (isValidWall(ny, nx)) return randint;
    return createWall(y, x);
}

void generate(int y, int x) {
    // 通路:0
    // 壁  :1
    for (int i = 0; i < x; i++) {
        field[0][i] = field[y - 1][i] = 1;
    }
    for (int i = 0; i < y; i++) {
        field[i][0] = field[i][x - 1] = 1;
    }

    for (int i = 2; i < y - 1; i += 2) {
        for (int j = 2; j < x - 1; j += 2) {
            field[i][j] = 1;
        }
    }

    for (int i = 2; i < y - 1; i += 2) {
        for (int j = 2; j < x - 1; j += 2) {
            int randint = createWall(y, x);
            int nx = j + dx[randint], ny = i + dy[randint];
            field[ny][nx] = 1;
        }
    }

    field[1][1] = 2;
    field[y - 2][x - 2] = 3;
}

void print(int y, int x) {
    static const char *display = " #SG";
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            printf("%c", display[field[i][j]]);
        }
        puts("");
    }
}

int main(void) {
    srand(time(NULL));
    int h = 19, w = 29;
    printf("input h, w : ");
    scanf("%d %d", &h, &w);
    generate(h, w);
    print(h, w);
}
