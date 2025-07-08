section .data
    string1 DB "ABC"
    string2 DB "CDE"

section .text
global _start

_start:
    MOV al,[string1]
    INT 80h