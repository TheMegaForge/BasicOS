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


;extern char* _drvGetTb(const char* drv);
global _drvGetTb
_drvGetTb:
    push ebp;4
    mov ebp,esp

    mov eax,[ebp+8]
    
    mov esp,ebp
    pop ebp
    ret

;extern void _drvIncOrResetInc(const int* ci);
global _drvIncOrResetInc
_drvIncOrResetInc:
    push ebp 
    mov ebp,esp
    mov eax,[ebp+8];ci
    cmp [eax],byte 19
    jl .Increment
    jmp .Shrink
    .Increment:
        inc byte [eax]
        jmp .ShrinkEnd
    .Shrink:
        mov byte [eax],0
    .ShrinkEnd:
    mov esp,ebp
    pop ebp
    ret


global fgets_secure
fgets_secure:
    ret