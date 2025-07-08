section .data

section .text
global _start

add_two:
    ADD eax,ebx
    RET

_start:
    MOV eax,4
    MOV ebx,2
    CALL add_two
    MOV ebx,eax
    MOV eax,1
    INT 80h