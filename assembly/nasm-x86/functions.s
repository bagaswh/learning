section .data

section .text
global _start

add_two:
    mov eax,10
    mov ebx,20
    add eax,ebx
    ret

_start:
    call add_two
    int3

    mov eax,1
    mov ebx,1
    int 80h
