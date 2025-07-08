#include <stdio.h>

void cat_meow(int loudness)
{
    printf("meowing at loudness %d\n", loudness);
}

void cat_sleep(char *where)
{
    printf("sleeping at %s\n", where);
}

void cat_scratch(char *where, int strength)
{
    printf("scratching %s with as strong as %d\n", where, strength);
}
