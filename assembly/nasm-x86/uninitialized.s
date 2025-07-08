section .data
    num6 DB 3 DUP(2)

section .bss
    num1 RESB 1
    num2 RESB 1
    num3 RESB 1
    num4 RESB 1
    num5 RESB 4

section .text
global _start

_start:
    MOV al,1
    MOV ah,1
    MOV bl,1
    MOV bh,1
    MOV [num1],al
    MOV [num2],ah
    MOV [num3],bl
    MOV [num4],bh

    MOV cl,1
    MOV ch,2
    MOV dl,3
    MOV dh,4
    MOV [num5],cl
    MOV [num5+1],ch
    MOV [num5+2],dl
    MOV [num5+3],dh

    MOV ecx,[num6]
    
    MOV eax,1
    INT3
    INT 80h