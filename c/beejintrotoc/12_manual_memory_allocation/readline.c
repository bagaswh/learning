//
// Created by bagaswh on 5/20/25.
//

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

struct slice {
    size_t cap, len, elem_size;
    void *buf;
};

struct slice *slice_new(const size_t len, const size_t cap, const size_t elem_size) {
    if (cap < len) {
        return NULL; // Capacity must be at least as large as length
    }

    struct slice *s = calloc(1, sizeof(struct slice));
    if (s == NULL) {
        return NULL;
    }
    s->cap = cap;
    s->len = len;
    s->elem_size = elem_size;

    void *buf = calloc(cap, elem_size);
    if (buf == NULL) {
        free(s);
        return NULL;
    }
    s->buf = buf;
    return s;
}

size_t slice_grow_cap(size_t old_cap) {
    // Similar to Go's growth strategy
    if (old_cap < 1024) {
        return old_cap * 2;
    } else {
        return old_cap + (old_cap / 4); // Grow by 25% once we reach 1024
    }
}

struct slice *slice_append(struct slice *sl, const void *data) {
    if (sl == NULL || data == NULL) {
        return NULL;
    }

    // Check if we need to grow
    if (sl->len >= sl->cap) {
        size_t new_cap = slice_grow_cap(sl->cap);
        void *new_buf = realloc(sl->buf, new_cap * sl->elem_size);
        if (new_buf == NULL) {
            return NULL;
        }
        sl->buf = new_buf;
        sl->cap = new_cap;
    }

    // Calculate the destination address
    char *dest = ((char *) sl->buf) + (sl->len * sl->elem_size);

    // Copy the new element
    memcpy(dest, data, sl->elem_size);
    sl->len++;

    return sl;
}

// Get a pointer to an element at index i
void *slice_get(const struct slice *sl, size_t i) {
    if (sl == NULL || i >= sl->len) {
        return NULL;
    }

    return (char *)sl->buf + (i * sl->elem_size);
}

// Set an element at index i
int slice_set(struct slice *sl, size_t i, const void *data) {
    if (sl == NULL || i >= sl->len || data == NULL) {
        return -1;
    }

    void *dest = (char *)sl->buf + (i * sl->elem_size);
    memcpy(dest, data, sl->elem_size);
    return 0;
}

void slice_free(struct slice *sl) {
    if (sl) {
        free(sl->buf);
        free(sl);
    }
}

struct slice *slice_set_len(struct slice *sl, size_t len) {
    if (sl == NULL) {
        return NULL;
    }

    const size_t new_len = (len*sl->elem_size);
    if (new_len > (sl->cap*sl->elem_size)) {
        return NULL;
    }

    sl->len  = new_len;
}

void slice_print_int(const struct slice *sl) {
    if (sl == NULL) {
        return;
    }

    printf("slice len=%lu cap=%lu elem_size=%lu\n", sl->len, sl->cap, sl->elem_size);
    printf("[");
    for (size_t i = 0; i < sl->len; i++) {
        int *value = (int *)slice_get(sl, i);
        printf("%d", *value);
        if (i < sl->len - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void slice_print_char(const struct slice *sl) {
    if (sl == NULL) {
        return;
    }

    printf("slice len=%lu cap=%lu elem_size=%lu\n", sl->len, sl->cap, sl->elem_size);
    printf("[");
    for (size_t i = 0; i < sl->len; i++) {
        char *value = (char *)slice_get(sl, i);
        printf("'%c'", *value);
        if (i < sl->len - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Generic print function that uses a callback for each element
void slice_print(const struct slice *sl, void (*print_elem)(const void *elem)) {
    if (sl == NULL || print_elem == NULL) {
        return;
    }

    printf("slice len=%lu cap=%lu elem_size=%lu\n", sl->len, sl->cap, sl->elem_size);
    printf("[");
    for (size_t i = 0; i < sl->len; i++) {
        void *elem = slice_get(sl, i);
        print_elem(elem);
        if (i < sl->len - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Example callback functions for print_elem
void print_int_elem(const void *elem) {
    printf("%d", *(int *)elem);
}

void print_char_elem(const void *elem) {
    printf("'%c'", *(char *)elem);
}

int slice_test() {
    // Test with integers
    struct slice *int_slice = slice_new(0, 4, sizeof(int));
    if (int_slice == NULL) {
        fprintf(stderr, "Failed to create int slice\n");
        return 1;
    }

    printf("Integer slice test:\n");
    for (int i = 0; i < 10; i++) {
        int value = i * 10;
        if (slice_append(int_slice, &value) == NULL) {
            fprintf(stderr, "Failed to append to int slice\n");
            slice_free(int_slice);
            return 1;
        }
    }

    slice_print(int_slice, print_int_elem);

    // Example: get and modify an element
    int *third_elem = (int *)slice_get(int_slice, 2);
    if (third_elem) {
        printf("Third element was: %d\n", *third_elem);
        *third_elem = 999;
        printf("Third element now: %d\n", *third_elem);
    }

    slice_print(int_slice, print_int_elem);

    // Test with characters
    struct slice *char_slice = slice_new(0, 4, sizeof(char));
    if (char_slice == NULL) {
        fprintf(stderr, "Failed to create char slice\n");
        slice_free(int_slice);
        return 1;
    }

    printf("\nCharacter slice test:\n");
    const char *test_str = "Hello, world!";
    for (size_t i = 0; i < strlen(test_str); i++) {
        char c = test_str[i];
        if (slice_append(char_slice, &c) == NULL) {
            fprintf(stderr, "Failed to append to char slice\n");
            slice_free(int_slice);
            slice_free(char_slice);
            return 1;
        }
    }

    slice_print(char_slice, print_char_elem);

    // Free memory
    slice_free(int_slice);
    slice_free(char_slice);
}

size_t slice_getline(FILE *f, struct slice *s) {
    if (s == NULL || s->elem_size != sizeof(int)) {
        return 1;
    }

    char *line;
    int c;
    size_t n = 0;
    while (c = fgetc(f), c != '\n' && c != EOF) {
        slice_append(s, &c);
        n++;
    }

    return n;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: ./program <huge file>");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "failed to open file: %s\n", strerror(errno));
        return 1;
    }

    struct slice *s = slice_new(0, 10, sizeof(int));
    while (slice_getline(f, s) != 0) {
        printf("%s\n", (int*)s->buf);
    }

    return 0;
}