.intel_syntax noprefix
.data
my_float:
    .float 78.1

my_byte:
    .byte 10

my_long:
    .long 10000

.text
.global _start
_start:
	mov eax, DWORD PTR my_float[rip]
	mov edi, DWORD PTR my_long[rip]
    
    mov DWORD PTR my_long[rip], 25000
    lea rsi, my_long
    mov dword ptr [rsi], 81273

    int3
