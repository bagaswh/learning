section .data
    arr1 db 1,2,3,4,5


section .text
global _start

_start:
    MOV al,0
    MOV ecx,0

loop:
    ADD al,[arr1+ecx]
    INC ecx
    CMP ecx,4
    JLE loop
    JMP end

end:
    INT3
    MOV eax,1
    MOV ebx,1
    INT 80h