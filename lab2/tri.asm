section .data
    fmt_in  db "%d", 0
    fmt_out db "%d", 10, 0

section .bss
    N   resd 1
    num resd 1
    sum resd 1

section .text
    global main
    extern scanf
    extern printf

main:
    push rbp
    mov rbp, rsp

    ; ввод N
    mov rdi, fmt_in
    lea rsi, [rel N]
    xor eax, eax
    call scanf

    mov dword [sum], 0
    mov ecx, [N]

read_numbers:
    cmp ecx, 0
    je output

    ; ввод числа
    mov rdi, fmt_in
    lea rsi, [rel num]
    xor eax, eax
    call scanf

    mov eax, [num]

digits:
    cmp eax, 0
    je next_num

    mov ebx, 10
    xor edx, edx
    div ebx            ; EAX=temp/10, EDX=temp%10

    cmp edx, 0
    je add_digit
    cmp edx, 3
    je add_digit
    cmp edx, 6
    je add_digit
    cmp edx, 9
    je add_digit

    jmp digits

add_digit:
    add [sum], edx
    jmp digits

next_num:
    dec ecx
    jmp read_numbers

output:
    mov rdi, fmt_out
    mov esi, [sum]
    xor eax, eax
    call printf

    xor eax, eax
    leave
    ret
