
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

dskPrope:
    push edx
    push eax
    mov dx,0x1f7
    in al,dx
    push eax
    mov dx,0x1f1
    in al,dx
    pop eax
    pop eax
    pop edx
    ret
[extern readContent]
[extern sendDSKEOI]
global dskRead
dskRead:
    push ebp
    mov ebp,esp
    push ecx
    push eax
    push edx
.loop:
    mov eax,[ebp+8];info
    mov edx,[eax];ptr
    mov ecx,[edx]
    cmp ecx,0
    je .loop
    .ready:
        cli
        mov eax,[ebp+8]
        push eax
        call readContent
        pop eax
        call sendDSKEOI
        sti
    .readyEnd:
    pop edx
    pop  eax
    pop  ecx
    mov esp,ebp
    pop ebp
    ret