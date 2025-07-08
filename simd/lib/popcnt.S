.intel_syntax noprefix

.text
.global main

main:
        push    rbp
        mov     rbp, rsp

        lea     rdi, [rip + .L.str]
        mov eax, 0b101001
        popcnt esi, eax
        call    printf@PLT

        pop     rbp
        ret

.L.str:
        .asciz  "%d\n"