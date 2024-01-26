[bits 32]
extern ISR_HANDLE

isr_common:
    pusha 
    xor eax,eax
    mov ax,dx
    push eax

    mov ax,0x10
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    push ebp
    call ISR_HANDLE
    add esp,4
    pop eax
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov gs,ax
    popa
    add esp,8
    iret