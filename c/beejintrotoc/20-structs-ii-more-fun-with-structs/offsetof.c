//
// Created by bagaswh on 5/21/25.
//

#include <stddef.h>
#include <stdio.h>

struct foo {
    int a;
    char b;
    int c;
    char d;
};

int main() {
    printf("%zu\n", offsetof(struct foo, a));
    printf("%zu\n", offsetof(struct foo, b));
    printf("%zu\n", offsetof(struct foo, c));
    printf("%zu\n", offsetof(struct foo, d));
}