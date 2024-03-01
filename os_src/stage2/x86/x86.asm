;RawFunction __cdecl void getHandles(void* sloc);
global getHandles
getHandles:
    push eax
    mov eax,[esp+8];sloc
    int 100
    pop eax
    ret

;extern IRQHandler getIRQ12();

;extern __cdecl bool probeIfRight(uint8_t fv,uint8_t sv);
global probeIfRight
probeIfRight:
    push ebp
    mov ebp,esp
    push edx
    push ebx

    xor edx,edx
    xor eax,eax ;clear

    mov edx,[ebp+4];sv
    mov eax,[ebp+8];fv

    cmp al,0xFA ;CMD_ACK
    je ._suc
    jmp ._noDev
    ._suc:
    cmp dl,0xAA
    je .suc
    jmp .fail
    .suc:
        mov eax,1
        jmp ._noDevEnd
    .fail:
        mov eax,0
        jmp ._noDevEnd
    ._noDev:
        mov eax,3
    ._noDevEnd:
    pop ebx
    pop edx
    mov esp,ebp
    pop ebp
    ret