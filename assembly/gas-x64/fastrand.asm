    .intel_syntax noprefix

    .data
g_seed: .quad 0
format: .asciz "rand: %d\n"

    .bss
.lcomm ts, 16

.text
    .global _start

init_seed:
    xor     rax, rax
    mov     [ts], rax
    mov     [ts+8], rax
    
    mov     rdi, 0
    lea     rsi, ts
    call    clock_gettime
    mov     rdi, qword ptr [ts]
    mov     qword ptr [g_seed], rdi

    ret

fastrand:
    mov     rdi, qword ptr [g_seed]
    /* g_seed = (214013*g_seed+2531011); */
    /* 214013*g_seed */
    mov     rax, rdi
    mov     rbx, 214013
    mul     rbx     # rax = low 64 bits of result

    add     rax, 2531011

    mov     qword ptr [g_seed], rax

    /* (g_seed>>16)&0x7FFF */
    shr     rax, 16
    and     rax, 0x7FFF

    # int3
    ret

_start:
    call    init_seed
    
loop:
    call    fastrand
    lea     rdi, format
    mov     rsi, rax
    call    printf
    jmp     loop

    mov     rax, 60
    mov     rdi, 0
    syscall
