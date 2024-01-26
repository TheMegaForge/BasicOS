;extern __attribute__((cdecl)) uint8_t LeftRoll8(uint8_t num,uint8_t rolls);
global LeftRoll8
LeftRoll8:
        
    push ebp
    mov ebp,esp
    push ecx


    xor ecx,ecx
    xor eax,eax

    mov ecx,[ebp+12]
    mov eax,[ebp+8]
    rol al,cl

    pop ecx
    mov esp,ebp
    pop ebp
    ret
;extern __attribute__((cdecl)) uint16_t LeftRoll16(uint16_t num,uint8_t rolls);
global LeftRoll16
LeftRoll16:
    
    push ebp
    mov ebp,esp
    push ecx


    xor ecx,ecx
    xor eax,eax

    mov ecx,[ebp+12]
    mov eax,[ebp+8]
    rol ax,cl

    pop ecx
    mov esp,ebp
    pop ebp
    ret
;extern __attribute__((cdecl)) uint32_t LeftRoll32(uint32_t num,uint8_t rolls);
global LeftRoll32
LeftRoll32:
    
    push ebp
    mov ebp,esp
    push ecx


    xor ecx,ecx
    xor eax,eax

    mov ecx,[ebp+12]
    mov eax,[ebp+8]
    ror eax,cl

    pop ecx
    mov esp,ebp
    pop ebp
    ret
;extern __attribute__((cdecl)) uint8_t RightRoll8(uint8_t num,uint8_t rolls);
global RightRoll8
RightRoll8:
    push ebp
    mov ebp,esp
    push ecx


    xor ecx,ecx
    xor eax,eax

    mov ecx,[ebp+12]
    mov eax,[ebp+8]
    ror al,cl

    pop ecx
    mov esp,ebp
    pop ebp
    ret
;extern __attribute__((cdecl)) uint16_t RightRoll16(uint16_t num,uint8_t rolls);
global RightRoll16
RightRoll16:
    push ebp
    mov ebp,esp
    push ecx


    xor ecx,ecx
    xor eax,eax

    mov ecx,[ebp+12]
    mov eax,[ebp+8]
    ror ax,cl

    pop ecx
    mov esp,ebp
    pop ebp
    ret
;extern __attribute__((cdecl)) uint32_t RigthRoll32(uint32_t num,uint8_t rolls);
global RightRoll32
RightRoll32:
    push ebp
    mov ebp,esp
    push ecx


    xor ecx,ecx
    xor eax,eax

    mov ecx,[ebp+12]
    mov eax,[ebp+8]
    ror eax,cl

    pop ecx
    mov esp,ebp
    pop ebp
    ret
