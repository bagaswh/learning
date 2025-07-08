#ifndef IS_DIGIT_H
#define IS_DIGIT_H

typedef short bool;
typedef unsigned char uchar;

bool is_digit(uchar c)
{
    return c - 48 <= 9;
}

#endif // IS_DIGIT_H