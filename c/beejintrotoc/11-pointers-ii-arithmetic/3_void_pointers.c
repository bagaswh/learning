//
// Created by bagaswh on 5/19/25.
//

#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(typeof((x)[0])))
#define BYTE_SIZE(x, n) (sizeof(typeof((x)[0])) * (n))

void memcpy_1() {
    int a[] = {11311188, 22, 33};
    int b[3] = {0};

    memcpy(b, a, 4);

    printf("%d\n", b[0]);
}

void void_star_conversion() {
    char a = 'X';
    void *p = &a;
    char *q = p;
    // printf("%c\n", *p);
    printf("%c\n", *q);
}

void *my_memcpy(void *dest, void *src, int n) {
    char *s = src, *d = dest;

    while (n--) {
        *d++ = *s++;
    }

    return dest;
}

int main() {
    // memcpy_1();
    // void_star_conversion();
    int a[] = {1, 2, 3, 4, 5}, b[5];
    my_memcpy(b, a, BYTE_SIZE(a, 5));
    for (int i = 0; i < ARRAY_SIZE(a); i++) {
        printf("%d ", b[i]);
    }
}