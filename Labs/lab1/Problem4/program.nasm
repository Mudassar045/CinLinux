global main
SECTION .data
SECTION .text
main:
mov rax,0
mov rdi,0
mov rsi, 15
syscall

mov r15,rax
mov rdi,60
mov rdi,r15
syscall
