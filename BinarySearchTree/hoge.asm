bits 64
section .text

; recFunc(int x);
global recFunc
recFunc:
    push    rbp
    mov     rbp, rsp
    sub     rsp, 0x10
    test    rdi, 0x00
    je      H1
    mov     [rbp - 0x04], rdi
    mov     rax, [rbp - 0x04]
    sub     rax, 0x01
    mov     rdi, rax
    call    recFunc
    pop     rbp
    ret

H1:
    mov     rax, 0x0A
    pop     rbp
    ret     0x00


