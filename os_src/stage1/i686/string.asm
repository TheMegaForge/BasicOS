;extern __attribute__((cdecl)) int countStructuresInMemorySpace(void* beg,void* end,unsigned char structSize);
global countStructuresInMemorySpace
countStructuresInMemorySpace:
    push ebp
    mov ebp,esp
    push ebx
    push ecx
    push edx
    xor edx,edx
    mov ebx,[ebp+8];beg
    mov ecx,[ebp+12];end
    sub ebx,ecx
    xor eax,eax
    mov eax,ebx;range -> eax
    mov ecx,[ebp+16];structSize
    div ecx;range/structSize
    pop edx
    pop ecx
    pop edx
    mov esp,ebp
    pop ebp
    ret
;extern __attribute__((cdecl)) unsigned char extractByte(uint32_t number,uint32_t mask,uint8_t rightShift);
global extractByte
extractByte:
    push ebp
    mov ebp,esp
    push ecx
    push ebx
    push edx

    xor ecx,ecx
    xor ebx,ebx
    xor edx,edx

    mov ecx,[ebp+16];rightShift
    mov ebx,[ebp+8];number
    mov edx,[ebp+12];mask

    and ebx,edx
    shr ebx,cl
    
    mov eax,ebx

    pop edx
    pop ebx
    pop ecx
    mov esp,ebp
    pop ebp
    ret