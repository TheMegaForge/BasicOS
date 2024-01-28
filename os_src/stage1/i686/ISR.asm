[bits 32]
extern ISR_HANDLE

%macro ISR_NOERR 1

global i686_ISR%1:
i686_ISR%1:
    push 0              ; push dummy error code
    push %1             ; push interrupt number
    jmp isr_common

%endmacro

%macro ISR_ERR 1
global i686_ISR%1:
i686_ISR%1:
                        ; cpu pushes an error code to the stack
    push %1             ; push interrupt number
    jmp isr_common

%endmacro
%include "os_src/stage1/i686/inc/isrs.inc"
%define TMP_HANDLER_VALUE 0x7BE0
isr_common:
    pushad               ; pushes in order: eax, ecx, edx, ebx, esp, ebp, esi, edi

    xor eax, eax        ; push ds
    mov ax, ds
    push eax

    mov ax, 0x10        ; use kernel data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    
    push esp            ; pass pointer to stack to C, so we can access all the pushed information
    call ISR_HANDLE     
    mov [0x7BE0],eax
    add esp, 4

    pop eax             ; restore old segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    popad                ; pop what we pushed with pushad
    mov eax,dword [0x7BE0]
    add esp, 8          ; remove error code and interrupt number
    iret
;extern int isrTest();
global isrTest
isrTest:
    int 35
    ret