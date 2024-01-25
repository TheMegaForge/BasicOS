[bits 16]
org 0x7e00
start:
    mov ax,word [esp+2]
    push ebp
    mov ebp,esp
    mov si,idSpec
    call ax
    call getMemoryInfo
    call hasPCI
    mov esp,ebp
    pop ebp
    ret

hasPCI:
    pusha
    xor edi,edi
    xor eax,eax
    xor edx,edx
    xor ecx,ecx
    xor ebx,ebx
    mov ax,0xb101
    int 0x1A
    cmp eax,1
    jne .h2Mek
    jmp .n2Mek
    .h2Mek:
        mov [0x7BFE],word 0b1000000000000000
        jmp .l2Mek
    .n2Mek:
        mov [0x7BFE],word 0
    .l2Mek:
    popa
    ret
%define MEM_MAP_STORE_LOC 0x8000
;
; ax = list
;
getMemoryInfo:
    push edx
    push ecx
    push ebx
    push eax
    push 0  ;stack init
    xor edx,edx
    xor ecx,ecx
    xor ebx,ebx
    xor eax,eax
    mov di,MEM_MAP_STORE_LOC
    .Mloop:
        call getInterrupt
        pop ax
        cmp ax,0
        je .MEnd
        pop cx
        cmp cx,20
        je .Expand
        jmp .ExpandL
        .Expand:
            mov [di+20],dword 0xFFFFFFFF
        .ExpandL:
            inc word [esp]
            add di,24
        jmp .Mloop
    .MEnd:
    pop ax
    pop ax  ;stack clean
    pop eax
    pop ebx
    pop ecx
    pop edx
    ret
;
;stack 1 = 0|0,1 = list end,1 = !end
;stack 2 = further data
getInterrupt:
    pop si
    xor eax,eax
    xor ecx,ecx
    mov edx,0x534D4150
    mov eax,0xE820
    mov ecx,24
    int 0x15
    jc .ErrTest
    jmp .ErrTestL
    .ErrTest:
        call TestError
    .ErrTestL:
        push cx
        push bx
        push si
        ret
TestError:
    ret
%define ENDL 0x0A,0x0D
SIZE_PER_LIST: db 24
id:db "THIS IS THE ADVANCED REAL SECTOR!",0
idSpec:db "ARSN2!",ENDL,0
M_INVALID_ERR:db "[ERROR] Can not get memory map!Because The BIOS does not support it!",ENDL,0
times 512-($-$$) db 0