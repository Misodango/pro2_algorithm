#include <stdio.h>

int main(void) {
    char s[] = "I will ace all tests\n";
    const int shift = 7;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] = (s[i] - 'a' + shift) % 26 + 'a';
        } else if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] = (s[i] - 'A' + shift) % 26 + 'A';
        }
    }
    printf("%s\n", s);
}
