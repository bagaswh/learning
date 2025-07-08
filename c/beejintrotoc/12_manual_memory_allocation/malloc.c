//
// Created by bagaswh on 5/19/25.
//

#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate space for a single int (sizeof(int) bytes-worth):
    int *p = malloc(sizeof(int));
    *p = 12;
    // Store something there
    printf("%d\n", *p);
    free(p);
    // Print it: 12
    // All done with that memory
    *p = 3490;
    printf("%d\n", *p);
    // ERROR: undefined behavior! Use after free()!
}
