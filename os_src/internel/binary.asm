
;extern __attribute__((cdecl)) uint16_t extractWordFromDWord(uint32_t dword,bool isUpper);
global extractWordFromDWord
extractWordFromDWord:
    push ebp
    mov ebp,esp
    push ebx
    push ecx

    mov ebx,[ebp+8];dword
    cmp [ebp+12],dword 1
    je .ReadUpper
    mov eax,ebx
    and eax,0x0000FFFF

    jmp .ReadUpperL
    .ReadUpper:
        mov eax,ebx
        and eax,0xFFFF0000
        shr eax,16
    .ReadUpperL:
    pop ecx
    pop ebx
    mov esp,ebp
    pop ebp
    ret
;extern __attribute__((cdecl)) uint8_t extractByteFromWord(uint16_t word,bool isUpper);
global extractByteFromWord
extractByteFromWord:
    push ebp
    mov ebp,esp
    push ebx
    push ecx
    
    mov ebx,[ebp+8];word
    cmp [ebp+12],dword 1
    je .ReadUpper
        mov ax,bx
        and ax,0x00FF
    jmp .ReadUpperL
    .ReadUpper:
        mov ax,bx
        and ax,0xFF00
        shr ax,8
    .ReadUpperL:
    pop ecx
    pop ebx
    mov esp,ebp
    pop ebp
    ret