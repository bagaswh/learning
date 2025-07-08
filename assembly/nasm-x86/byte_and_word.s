section .data
    num1 db 1
    num2 db 2

section .text
global _start

_start:
    MOV bl,[num1]
    MOV bh,[num2]
    MOV eax,ebx

    MOV ebx,2
    INT3
    INT 80h