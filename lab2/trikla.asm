section .data
    fmt_in db "%d", 0
    fmt_out db "%d", 10, 0

section .bss
    n resd 1
    num resd 1
    sum resd 1
    i resd 1

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

    mov dword [sum], 0
    mov dword [i], 0

read_loop:
    mov eax, [i]
    cmp eax, [n]
    jge print_result

    mov rdi, fmt_in
    lea rsi, [num]
    xor eax, eax
    call scanf

    mov eax, [num]

digit_loop:
    cmp eax, 0
    je next_num

    xor edx, edx
    mov ebx, 10
    div ebx

    cmp edx, 0
    je add_digit
    cmp edx, 3
    je add_digit
    cmp edx, 6
    je add_digit
    cmp edx, 9
    je add_digit
    jmp digit_loop

add_digit:
    add [sum], edx
    jmp digit_loop

next_num:
    inc dword [i]
    jmp read_loop

print_result:
    mov rdi, fmt_out
    mov esi, [sum]
    xor eax, eax
    call printf

    xor eax, eax
    leave
    ret
