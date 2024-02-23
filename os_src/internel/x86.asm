
;extern __attribute__((cdecl)) uint32_t regDriverINT(int id,int subID,void* addr)
global regDriverINT
regDriverINT:
    push ebp
    mov ebp,esp
    push ebx
    push ecx
    push edx

    mov ecx,[ebp+8];addr
    mov edx,[ebp+12];subID
    mov ebx,[ebp+16];id
    mov eax,0
    
    int 60
    pop edx
    pop ecx
    pop ebx
    mov esp,ebp
    pop ebp
    ret
;extern __attribute__((cdecl)) void*    getDriverINT(int id,int subID);
global getDriverINT
getDriverINT:
    push ebp
    mov ebp,esp

    push ebx
    push ecx

    mov ebx,[ebp+8];subID
    mov ecx,[ebp+12];id

    mov eax,1
    int 60

    
    pop ecx
    pop ebx




    mov esp,ebp
    pop ebp

    ret


[extern readContent]
[extern sendDSKEOI]
global dskRead
dskRead:
    push ebp
    mov ebp,esp

    xor eax,eax
    xor edx,edx
    xor ecx,ecx
    xor edi,edi

    mov ecx,[ebp+8];intInfo
    mov edx,[ecx]  ;isReady
    mov edi,[ecx+4];secs

.cmpLoop:
    mov ecx,[edi]
    cmp ecx,0
    jz .End
    cmp [edx],dword 1
    je .ready
    mov eax,[ebp+8];info
    jmp .readyEnd
    .ready:
        push eax
        call readContent
        call sendDSKEOI
        mov [edi],dword 0
    .readyEnd:
    jmp .cmpLoop
    .End:
    mov esp,ebp
    pop ebp
    ret