
#include <stddef.h>
#include <stdio.h>

struct foo {
    // since all of these are just 16 bits, which can fit in a single
    // unsigned int, it will be put in a single unsigned int
    // thus sizeof struct foo is 4
    unsigned int a:5;
    unsigned int b:5;
    unsigned int c:3;
    unsigned int d:3;
};

struct foo_s {
    unsigned short a:5;
    unsigned short b:5;
    unsigned short c:3;
    unsigned short d:3;
};

int main() {
    printf("%lu\n", sizeof(struct foo));

    // now, why this errors with
    // error: attempt to take address of bit-field structure member ‘d’
    // ???
    // well probably because abcd is actually put in a single unsigned int
    // printf("%zu\n", offsetof(struct foo, a));
    // printf("%zu\n", offsetof(struct foo, b));
    // printf("%zu\n", offsetof(struct foo, c));
    // printf("%zu\n", offsetof(struct foo, d));

    printf("%lu\n", sizeof(struct foo_s));
}