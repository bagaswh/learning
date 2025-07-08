#include <stdio.h>

void meow(int loudness) {
  printf("meowing at loudness %d\n", loudness);
}

void sleep(char *where) {
  printf("sleeping at %s\n", where);
}

void scratch(char *where, int strength) {
  printf("scratching %s with as strong as %d\n", where, strength);
}

