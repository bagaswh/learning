section .data
    num3 DD 2

section .text
global _start

_start:
    MOV eax,1
    MOV ebx,[num3]
    INT 80h