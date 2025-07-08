//
// Created by bagaswh on 5/21/25.
//

#include <stdint.h>
#include <stdio.h>

struct point {
    uint8_t x, y;
};

void f_point() {
    printf("-------------BEGIN f_point-------------");
    uint8_t xs[4] = {1,0,0,0};
    struct point p = {1, 1};
    uint32_t *pp = (void*)xs;
    printf("%d\n", *(uint16_t*)&p);
    printf("-------------END f_point-------------");
}

struct foo {
    char a;
    int b;
};

void f_foo() {
    struct foo x = {0x12, 0x12345678};
    unsigned char *p = (unsigned char *)&x;
    for (size_t i = 0; i < sizeof x; i++) {
        printf("%02X\n", p[i]);
    }
}


int main() {
    f_foo();
}