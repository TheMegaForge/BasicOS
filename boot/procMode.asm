org 0x7f00
bits 32
start:
    mov esp,0x0000F000
    mov ax,0x10
    mov ss,ax
    mov ds,ax
    call ProtMode
    mov cl,0x11
    call setScreenColor
    .LinePrint:

    mov cl,0x1F
    mov edi,0xb8000
    mov esi,osSpecLine0
    call putText
    mov bl,0x11
    call newLine

    xor cx,cx
    mov cl,0x1F
    mov edi,edx
    mov esi,osSpecLine1
    call putText
    mov bl,0x11
    call newLine

    xor cx,cx
    mov cl,0x1F
    mov edi,edx
    mov esi,osSpecLine2
    call putText
    mov bl,0x11
    call newLine
    xor cx,cx
    mov cl,0x1F
    mov edi,edx
    mov esi,osSpecLine3
    call putText
    mov bl,0x11
    call newLine
    
    .TEnd:
    xor eax,eax
    xor ecx,ecx
    .SetupCall:
        mov [0x0000F000],edx
    .SEnd:
    push 0x0000F000
    call 0x00000500     ; c-code
    cli
    hlt
%include "asm_include/boot/TextColors.inc"
%include "asm_include/utils/Bits.inc"
%define NATIVE_TALK_STORE_LOCATION 0x0000F000
hasCpuId: db 0
ProtMode:
    mov esi,idSpec
    mov edi,TEXT_BUFFER
    mov cl,WHITE_GREEN
    call putText
    call newLine
    mov edi,edx
    call is64bitMachine
    call hasSSEBasic
    call hasMMXBasic
    
    ret
is64bitMachine:
    push eax
    push ecx   
    push edx
    pushfd
    pop eax
    mov ecx,eax
    xor eax,1 << 21
    push eax
    popfd

    pushfd
    pop eax
    push ecx
    popfd
    xor eax,ecx
    jz .NoCpuid
    jmp .hasCpuid
    .NoCpuid:
        mov [hasCpuId],byte 0
        jmp .hasCpuidL
    .hasCpuid:
        mov [hasCpuId],byte 1
    .hasCpuidL:
    mov eax,0x80000001
    cpuid
    test edx,1<<29
    jz .N64Bit
    jmp .64Bit
    .N64Bit:
        add [0x7BFE],word 0
        jmp .64BitL
    .64Bit:
        add [0x7BFE],word 1
    .64BitL:
    pop edx
    pop ecx
    pop eax
    ret
hasSSEBasic:
    push eax
    push edx
    mov eax,0x1
    cpuid
    test edx,1<<25
    jz .nSSE
    jmp .hSSE
    .nSSE:
        jmp .SSEBasicL
    .hSSE:
        push ecx
        mov ax,[0x7BFE]
        mov cl,2
        call setBit
        mov [0x7BFE],ax
        pop ecx
    .SSEBasicL:
    pop edx
    pop eax
    ret
hasMMXBasic:
    push eax
    push edx
    mov eax,0x1
    cpuid
    test edx,1<<23
    jz .nMMX
    jmp .hMMX
    .nMMX:
        jmp .MMXL
    .hMMX:
        push ecx
        mov ax,[0x7BFE]
        mov cl,3
        call setBit
        mov [0x7BFE],ax
        pop ecx
    .MMXL:
    pop edx
    pop eax
    ret

%include "asm_include/boot/Text.inc"
%define PM_IS_LONG_MODE_POS 0x7BFE
;^ also stores sse,mmx,avx
id:db"THIS IS THE PROTECTED MODE SECTOR!",0
idSpec:db "Entered Stage : Booting (32 bit)",0
osSpecLine0:db "OS : Bos (Basic Operating System)",0
osSpecLine1:db "    (c)Mc Player : theMW",0
osSpecLine2:db "    https://de.namemc.com/profile/theMW.2",0
osSpecLine3:db "    https://github.com/TheMegaForge/BasicOS",0
times 4096-($-$$) db 0 