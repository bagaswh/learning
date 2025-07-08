#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

struct PoorlyAligned_4byte
{
    char a;
    int32_t b;
    char c;
};

struct PoorlyAligned_8byte
{
    char a;
    int64_t b;
    char c;
};

int main()
{
    struct PoorlyAligned_4byte pa4b = {};
    struct PoorlyAligned_8byte pa8b = {};

    printf("pa4b size=%lu; pa8b size=%lu\n", sizeof(pa4b), sizeof(pa8b));
    printf("-- pa4b offsets --\n");
    printf("-- a = %lu --\n", offsetof(struct PoorlyAligned_4byte, a));
    printf("-- b = %lu --\n", offsetof(struct PoorlyAligned_4byte, b));
    printf("-- c = %lu --\n", offsetof(struct PoorlyAligned_4byte, c));
    printf("-- pa8b offsets --\n");
    printf("-- a = %lu --\n", offsetof(struct PoorlyAligned_8byte, a));
    printf("-- b = %lu --\n", offsetof(struct PoorlyAligned_8byte, b));
    printf("-- c = %lu --\n", offsetof(struct PoorlyAligned_8byte, c));
}