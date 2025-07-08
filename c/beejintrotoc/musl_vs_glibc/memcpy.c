//
// Created by bagaswh on 5/19/25.
//

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 104857600 // 100 MiB

int main(const int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: ./prog <bigfile path>");
        return 1;
    }

    char *a = malloc(SIZE), *b = malloc(SIZE);
    memset(a, 0, SIZE);
    memset(b, 0, SIZE);

    // printf("------- zero values of a -----------");
    // printf("%d - %d\n", a[0], a[SIZE-1]);

    const FILE *bigfile = fopen(argv[1], "r");
    if (bigfile == NULL) {
        fprintf(stderr, "failed to open bigfile: %s", strerror(errno));
        return 1;
    }

    size_t n = fread(a, 1, SIZE, bigfile);
    if (n != SIZE) {
        fprintf(stderr, "fread() failed: %zu\n", n);
    }

    // printf("------- a after fread -----------");
    // printf("%d - %d\n", a[0], a[SIZE-1]);

    memcpy(b, a, SIZE);

    // printf("------- b after fread -----------");
    // printf("%d - %d\n", b[0], b[SIZE-1]);
}