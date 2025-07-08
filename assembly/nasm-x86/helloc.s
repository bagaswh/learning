extern printf
extern exit

section .data
    fmt DB "Hello, %s. Are you %s today?",10,0
    name DB "Bagas Wahyu Hidayah",0
    mood DB "happy",0

section .text
global main

main:
    PUSH mood
    PUSH name
    PUSH fmt
    CALL printf
    
    PUSH 0
    CALL exit
