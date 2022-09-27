global main
extern printf, scanf

section .data
    msg:        db "Enter a string: ", 0
    msg2:       db "Enter a number: ", 0
    fmt:        db "%s", 0
    s:          times 128 db 0 ; creates a string of 128-long null characters
    fmt2:       db "%d", 0
    fmtout:     db "Your number is %d", 10, 0
    fmtout2:    db "Your entered: %s", 10, 0

section .bss
    n resb 4


section .text

main:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 16

    mov     rdi, msg2
    xor     rax, rax
    call    printf
    
    ; setting up args for scanning int
    lea     rdi, [fmt2]
    lea     rsi, [n]
    xor     rax, rax ; rax zeroed out for return value
    call    scanf

    mov     rdi, msg
    xor     rax, rax
    call    printf

    ; setting up args for scanning string
    lea     rdi, [fmt]
    lea     rsi, [s]
    xor     rax, rax
    call    scanf
    
    ; setting up args for printing int
    lea     rdi, [fmtout]
    mov     rsi, [n]
    xor     rax, rax
    call    printf

    ; setting up args for printing string
    lea     rdi, [fmtout2]
    lea     rsi, [s]
    xor     rax, rax
    call    printf

    add     rsp, 16
    xor     rax, rax ; rax zeroed out for return value
    mov     rsp, rbp
    pop     rbp
    ret

