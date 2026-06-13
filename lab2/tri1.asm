section .data
    fmt_in db "%d", 0
    fmt_out db "%d", 10, 0

section .bss
    n resd 1
    cnt resd 1
    num resd 1
    sum resd 1

section .text
    global main
    extern scanf
    extern printf

main:
    push rbp
    mov rbp, rsp

    mov rdi, fmt_in
    lea rsi, [n]
    xor eax, eax
    call scanf

    mov eax, [n]
    mov [cnt], eax
    mov dword [sum], 0

read_numbers:
    cmp dword [cnt], 0
    je output

    mov rdi, fmt_in
    lea rsi, [num]
    xor eax, eax
    call scanf

    mov eax, [num]

digits:
    cmp eax, 0
    je next_num

    xor edx, edx
    mov ebx, 10
    div ebx

    cmp edx, 0
    je add
    cmp edx, 3
    je add
    cmp edx, 6
    je add
    cmp edx, 9
    je add
    jmp digits

add:
    add [sum], edx
    jmp digits

next_num:
    dec dword [cnt]
    jmp read_numbers

output:
    mov rdi, fmt_out
    mov esi, [sum]
    xor eax, eax
    call printf

    xor eax, eax
    leave
    ret