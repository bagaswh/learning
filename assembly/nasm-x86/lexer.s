extern is_digit
extern exit

section .data

section .text
global main

main:
    push '0'
    call is_digit
    INT3

    PUSH 0
    CALL exit