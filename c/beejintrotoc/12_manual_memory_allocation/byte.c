//
// Created by bagaswh on 5/20/25.
//

#include <stdint.h>
#include <stdio.h>

int main() {
    uint8_t a[4] = {0,0,0,1<<7};
    printf("%d\n", (*(uint32_t*)a)-1);
}
