#include <stdio.h>

union foo {
    int a, b, c, d, e, f;
    float g, h;
    char i, j, k, l;
};

void ptr_to_union_foo() {
    union foo x;

    int *foo_int_p = (int *)&x;
    float *foo_float_p = (float *)&x;
    x.a = 12;
    printf("%d\n", x.a);
    printf("%d\n", *foo_int_p);
    x.g = 3.14159;
    printf("%f\n", x.g);
    printf("%f\n", *foo_float_p);
}

void ptr_to_union() {
    union foo x;
    int *foo_int_p = (int*)&x;
    union foo *p = (union foo *)foo_int_p;
    p->a = 12; // this line is the same as...
    x.a = 12;  // this one
}

union foo_a {
    float b;
    short a;
};

void union_foo_a() {
    union foo_a x;
    x.b = 3.14159;
    printf("%f\n", x.b);
    printf("%d\n", x.a);
}


int main() {
    ptr_to_union_foo();
}