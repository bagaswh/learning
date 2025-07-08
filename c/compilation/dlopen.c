#include <dlfcn.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    void *p = dlopen(argv[1], RTLD_LAZY);
    if (p == NULL) {
        fprintf(stderr, "failed to dlopen: %s\n", dlerror());
    }
}