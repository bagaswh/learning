#define HELLO 1<<1

void printf(char *format, ...);

int main() {
    printf("Hello, World!\n", HELLO);
    return 0;
}