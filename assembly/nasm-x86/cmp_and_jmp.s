section .data

section .text
global _start

_start:
    MOV eax,3
    MOV ebx,2
    CMP eax,ebx
    JL lesser
_branch1:
    


    JMP end

lesser:
    MOV eax,1
    JMP _branch1

end:
    INT 80h