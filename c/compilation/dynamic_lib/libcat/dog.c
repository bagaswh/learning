#include <stdio.h>

void dog_bark(int loudness)
{
    printf("barking at loudness %d\n", loudness);
}

void dog_sleep(char *where)
{
    printf("dog's sleeping at %s\n", where);
}

void dog_poo(char *where, int strength)
{
    printf("dog pooing %s with as strong as %d\n", where, strength);
}
