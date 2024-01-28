[bits 32]
;__attribute__((cdecl)) void outb(unsigned short int port,uint8_t data);
global outb_
outb_:
    push eax
    push edx
    push ebp
    mov ebp,esp
    mov eax,[ebp+20]
    mov edx,[ebp+16]
    out dx,al
    mov esp,ebp
    pop ebp
    pop edx
    pop eax
    ret
;__attribute__((cdecl)) void outs(unsigned short int port,uint16_t data);
global outs_
outs_:
    push eax
    push edx
    push ebp
    mov ebp,esp
    mov eax,[ebp+20]
    mov edx,[ebp+16]
    out dx,ax
    mov esp,ebp
    pop ebp
    pop edx
    pop eax
    ret
;__attribute__((cdecl)) void outi(unsigned short int port,uint32_t data);
global outi_
outi_:
    push eax
    push edx
    push ebp
    mov ebp,esp
    mov eax,[ebp+20]
    mov edx,[ebp+16]
    out dx,eax
    mov esp,ebp
    pop ebp
    pop edx
    pop eax
    ret
;__attribute__((cdecl)) uint8_t inb(uint16_t port);
global inb_
inb_:
    push edx
    push ebp
    mov ebp,esp
    mov edx,[ebp+12]
    in al,dx
    mov esp,ebp
    pop ebp
    pop edx
    ret

;__attribute__((cdecl)) uint16_t ins(uint16_t port);
global ins_
ins_:
    push edx
    push ebp
    mov ebp,esp
    mov edx,[ebp+12]
    in ax,dx
    mov esp,ebp
    pop ebp
    pop edx
    ret
;__attribute__((cdecl)) uint32_t ini(uint16_t port);
global ini_
ini_:
    push edx
    push ebp
    mov ebp,esp
    mov edx,[ebp+12]
    in eax,dx
    mov esp,ebp
    pop ebp
    pop edx
    ret
;extern __attribute__((cdecl)) void io_wait();
global io_wait
io_wait:
    push edx
    push eax
    xor eax,eax
    mov dx,0x80
    out dx,al
    pop eax
    pop edx
    ret
global enableInterrupts
enableInterrupts:
    sti
    ret
    
global disableInterrupts
disableInterrupts:
    cli
    ret