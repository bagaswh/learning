.intel_syntax noprefix
.data
my_ints1:
    .long 0, 1, 2, 3

my_ints2:
    .long 5, 5, 5, 5

.text
.global _start
main:
    xorps xmm0, xmm0
    xorps xmm1, xmm1
    movdqu xmm0, xmmword ptr my_ints1[rip]
    movdqu xmm1, xmmword ptr my_ints2[rip]
    paddd xmm0, xmm1
    int3

    ret

_start:
    call main

    xor rdi, rdi
    mov rax, 0x3c
    