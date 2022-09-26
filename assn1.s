extern printf

SECTION .DATA
    msg:        db "Hello World", 0
    fmt:        db "%s", 10, 0

SECTION .TEXT
    global main

main:
    push rbp

    ; setting up args for printf
    mov rdi, fmt
    mov rsi, msg
    mov rax, 0
    call printf

    pop rbp
    mov rax, 0
    ret

