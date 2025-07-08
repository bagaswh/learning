section .data

section .text
global _start

add_two:
    ; int add_two(int a, int b)
    push ebp
    mov ebp, esp

    ; [BEGIN func body]
    ; a=[ebp+12]
    ; b=[ebp+8]
    mov eax,[ebp+12]
    add eax,[ebp+8]
    ; [END func body]

    pop ebp
    ret

sub_two:
    push ebp
    mov ebp, esp

    ; [BEGIN func body]
    ; a=[ebp+12]
    ; b=[ebp+8]
    mov eax,[ebp+12]
    sub eax,[ebp+8]
    ; [END func body]

    pop ebp
    ret

mul_two:
    push ebp
    mov ebp, esp

    ; [BEGIN func body]
    ; a=[ebp+12]
    ; b=[ebp+8]
    mov eax,[ebp+12]
    sub eax,[ebp+8]
    ; [END func body]

    pop ebp
    ret

_start:
    ;push 1
    ;push 2
    ;call add_two
    ;int3

    push 7
    push 2
    call sub_two
    int3

    int 80h

