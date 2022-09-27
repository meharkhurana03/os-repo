extern printf, scanf

section .data
    msg:        db "Hello World", 0
    fmt:        db "Enter a string: %s", 0
    s:          times 128 db 0 ; creates a string of 128-long null characters
    fmt2:       db "Enter a number: %d", 0
    fmtout:     db "Your number is %d", 0
    fmtout2:    db "Your entered: %s", 0


section .text
    global  main

main:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 4

    mov     rdi, msg
    xor     rax, rax
    call    printf
    
    ; setting up args for scanning int
    mov     rdi, fmt2   ; lea
    mov     rsi, [rbp-4]
    xor     rax, rax ; rax zeroed out for return value
    call    scanf

    ; setting up args for scanning string
    mov     rdi, fmt
    mov     rsi, s
    xor     rax, rax
    call    scanf
    
    ; setting up args for printing int
    mov     rdi, fmtout
    mov     rsi, [rbp-4]
    xor     rax, rax
    call    printf

    ; setting up args for printing string
    mov     rdi, fmtout2
    mov     rsi, s
    xor     rax, rax
    call    printf

    xor     rax, rax ; rax zeroed out for return value
    mov     rsp, rbp
    pop     rbp
    ret

