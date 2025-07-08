#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

int main() {
    time_t t;
    srand((unsigned)time(&t));
    int r_num = rand();
    double sr = sqrt(r_num);
    return 0;
}