
;extern __attribute__((packed)) uint8_t getUByteVarArg(void* bsp,uint8_t argPos);
;extern __attribute__((packed)) uint16_t getUShortVarArg(void* bsp,uint8_t argPos);
;extern __attribute__((packed)) uint32_t getUIntVarArg(void* bsp,uint8_t argPos);
;
;extern __attribute__((packed)) int8_t getByteVarArg(void* bsp,uint8_t argPos);
;extern __attribute__((packed)) int16_t getShortVarArg(void* bsp,uint8_t argPos);
;extern __attribute__((packed)) int32_t getIntVarArg(void* bsp,uint8_t argPos);
;
;extern __attribute__((packed)) const void* getAddressVarArg(void* bsp,uint8_t argPos);
ByteCommon:
    push esi
    push edx
    mov esi,edx
    mov eax,ecx
    mov ecx,4
    mul ecx
    add eax,esi
    mov ecx,eax

    mov eax,[ecx]

    mov cl,al
    xor eax,eax
    mov al,cl    ;disables overflow
    pop edx
    pop esi
    ret
WordCommon:
    push esi
    push edx
    mov edi,edx
    mov eax,ecx
    mov ecx,4
    mul ecx
    add eax,esi
    mov ecx,eax

    mov eax,[ecx]

    mov cx,ax
    xor eax,eax
    mov ax,cx    ;disables overflow
    pop edx
    pop esi
    ret
DWordCommon:
    push esi
    push edx
    mov esi,edx
    mov eax,ecx
    mov ecx,4
    mul ecx
    add eax,esi
    mov ecx,eax

    mov eax,[ecx]
    pop edx
    pop esi
    ret
global getUByteVarArg
getUByteVarArg:
    push ebp
    push ecx
    push edx
    mov ebp,esp
    xor ecx,ecx
    xor edx,edx

    mov ecx,[ebp+8];argPos
    mov edx,[ebp+4];bsp
   ; dec ecx
    call ByteCommon


    mov esp,ebp
    pop edx
    pop ecx
    pop ebp
    ret
global getUShortVarArg
getUShortVarArg:
    push ebp
    push ecx
    push edx
    mov ebp,esp
    xor ecx,ecx
    xor edx,edx

    mov ecx,[ebp+8];argPos
    mov edx,[ebp+4];bsp
   ; dec ecx
    call WordCommon
    


    mov esp,ebp
    pop edx
    pop ecx
    pop ebp
    ret
global getUIntVarArg
getUIntVarArg:
    mov ebp,esp
    push ebp
    push ecx
    push edx
    xor ecx,ecx
    xor edx,edx

    mov ecx,[ebp+8];argPos
    mov edx,[ebp+4];bsp
  ;  dec ecx
    call DWordCommon

    pop edx
    pop ecx
    pop ebp
    mov esp,ebp
    ret
global getByteVarArg
getByteVarArg:
    push ebp
    mov ebp,esp
    push ecx
    push edx
    xor ecx,ecx
    xor edx,edx

    mov ecx,[ebp+8];argPos
    mov edx,[ebp+4];bsp
   ; dec ecx
    call ByteCommon




    pop edx
    pop ecx
    mov esp,ebp
    pop ebp
    ret
global getShortVarArg
getShortVarArg:
    push ebp
    mov ebp,esp
    push ecx
    push edx
    xor ecx,ecx
    xor edx,edx

    mov ecx,[ebp+8];argPos
    mov edx,[ebp+4];bsp
  ;  dec ecx
    call WordCommon

    pop edx
    pop ecx
    mov esp,ebp
    pop ebp
    ret
global getIntVarArg
getIntVarArg:
    push ebp
    mov ebp,esp
    push ecx
    push edx
    xor ecx,ecx
    xor edx,edx

    mov ecx,[ebp+8];argPos
    mov edx,[ebp+4];bsp
   ; dec ecx
    call DWordCommon

    pop edx
    pop ecx
    mov esp,ebp
    pop ebp
    ret
global getAddressVarArg
getAddressVarArg:
    push ebp
    mov ebp,esp
    push ecx
    push edx
    xor ecx,ecx
    xor edx,edx

    mov ecx,[ebp+8];argPos
    mov edx,[ebp+4];bsp
  ;  dec ecx
    call DWordCommon


    pop edx
    pop ecx
    mov esp,ebp
    pop ebp
    ret