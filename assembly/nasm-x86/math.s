section .data

section .text
global _start

_start:
    MOV al,0b11111111
    MOV bl,0b0001
    ADD al,bl
    ADC al,0
    INT3

    INT 80h