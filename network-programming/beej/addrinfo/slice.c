//
// Created by bagaswh on 5/19/25.
//

#include <stddef.h>
#include "slice.h"

struct slice {
    size_t cap, len;
    void *data;
};