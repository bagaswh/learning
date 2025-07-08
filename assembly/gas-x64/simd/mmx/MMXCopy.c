#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

void MMXCopy(char *dst, char *src, int count);

int main() {

    char *dst = malloc(64);
    char *src = malloc(64);
    for (size_t i = 0; i < 64; i++) {
        src[i] = i;
        dst[i] = 0;
    }

    MMXCopy(dst, src, 64);

    for (size_t i = 0; i < 64; i++) {
        printf("src %d\n", src[i]);
        printf("dst %d\n", dst[i]);
    }

    free(dst);
    free(src);

}