[bits 16]
org 0x7c00
%define IS_LONG_MODE_POS 0x7BFE
%define ENDL 0x0A,0x0D
%define DISK_NUM 0x0
%define FS_BX_POS 0xBFC
%define FS_CX_POS 0xBFA
%define FS_DX_POS 0xBE8
%define USED_SECTORS_FOR_BM 5
start:
    mov ax,0
    mov ds,ax
    mov es,ax
    mov fs,ax
    mov sp,0x7c00
    mov ss,ax
    push ax
    jmp main
puts:
    push si
    push ax
    .loop:
        lodsb
        or al,al
        jz .done
        mov ah,0x0e
        int 0x10
        jmp .loop
    .done:
        pop ax
        pop si
        ret
getFileSystemInformation:
    pop si
    xor ax,ax
    mov ah,0x008
    mov dl,DISK_NUM
    mov dx,0
    mov es,dx
    mov di,dx
    int 0x13
    jc .ERR
    jmp .NORMAL
    .ERR:
        mov si,DISK_PARA_ERR
        call puts
        mov ah,0x0
        int 0x16
        jmp 0xFFFF:0
    .NORMAL:
        xor dh,dh
        push bx
        push cx
        push dx
    push si
ret
EnableA20:
    call A20WaitInput
    mov al, KbdControllerDisableKeyboard
    out KbdControllerCommandPort, al

    ; read control output port
    call A20WaitInput
    mov al, KbdControllerReadCtrlOutputPort
    out KbdControllerCommandPort, al

    call A20WaitOutput
    in al, KbdControllerDataPort
    push eax

    ; write control output port
    call A20WaitInput
    mov al, KbdControllerWriteCtrlOutputPort
    out KbdControllerCommandPort, al
    
    call A20WaitInput
    pop eax
    or al, 2                                    ; bit 2 = A20 bit
    out KbdControllerDataPort, al

    ; enable keyboard
    call A20WaitInput
    mov al, KbdControllerEnableKeyboard
    out KbdControllerCommandPort, al

    call A20WaitInput
    ret
A20WaitInput:
    ; wait until status bit 2 (input buffer) is 0
    ; by reading from command port, we read status byte
    in al, KbdControllerCommandPort
    test al, 2
    jnz A20WaitInput
    ret
A20WaitOutput:
    ; wait until status bit 1 (output buffer) is 1 so it can be read
    in al, KbdControllerCommandPort
    test al, 1
    jz A20WaitOutput
    ret
loadGDT:
    lgdt [GDT_descriptor]
    ret
;
; stack: store address
; al : number of sectors
; cl : begin sector
readDiskBasic:
    pop si
    pop bx
    push dx
    push cx
    push ax
    push ebp
    mov ebp,esp
    sub esp,2 ;init stack
    mov [ebp-2],word 3
    .Rloop:
        mov dh,0
        mov dl,0
        mov ch,0
        mov ah,0x02
        int 0x13
        dec word [ebp-2]
        cmp [ebp-2],word 0
        je .Error
        jc .Retry
        jmp .REnd
    .Retry:
        xor ah,ah
        jmp .Rloop
    .Error:
        mov si,REAL_SECTOR_ERR
        call puts
        mov ah,0x0
        int 0x16
        jmp 0xFFFF:0
    .REnd:   
    add esp,2 ;clear stack
    mov esp,ebp
    pop ebp
    pop ax
    pop cx
    pop dx
    push si
    ret
;readAdvancedReal:
;    push ax
;    push cx
;    push bx 
;    push ebp
;    mov ebp,esp
;    sub esp,2 ;init stack
;    mov [ebp-2],word 3
;    .Rloop:
;        mov ah,0x02
;        mov al,1
;        mov ch,0
;        mov cl,2
;       mov dh,0
;       mov dl,0
;       mov bx,0x7e00
;       int 0x13
;       dec word [ebp-2]
;       cmp [ebp-2],word 0
;       je .Error
;       jc .Retry
;       jmp .Rend
;   .Retry:
;       xor ah,ah
;       jmp .Rloop
;   .Error:
;       mov si,REAL_SECTOR_ERR
;       call puts
;       add esp,2
;       mov esp,ebp
;       pop ebp
;       pop bx
;       pop cx
;       pop ax
;       mov ah,0x0
;       int 0x16
;       jmp 0xFFFF:0
;   .Rend:
;   add esp,2 ;clear stack
;   mov esp,ebp
;   pop ebp
;   pop bx 
;   pop cx
;   pop ax
;   ret
main:
    mov si,BOOT_MSG
    call puts
    call getFileSystemInformation
    mov ax,0
    mov es,ax

    push puts
    mov al,1
    mov cl,2
    push 0x7e00         ;AR(Advanced Real)
    call readDiskBasic  ;AR(Advanced Real)
    call 0x7e00         ;AR(Advanced Real)
    ;1 = boot
    ;2 = AR
    ;2-10 = procMode
    mov al,42            ;setup: 16sects = 8192,32sects = 16384,64sects = 32768
    mov cl,11               
    push 0x00000500
    call readDiskBasic  
    mov al,4         
    mov cl,3
    push 0x7f00         ;BP(Basic Protected)
    call readDiskBasic  ;BP(Basic Protected)
    cli
    call EnableA20
    call loadGDT
    mov eax,cr0
    or al,1
    mov cr0,eax
    jmp dword 0x8:0x7f00
;[bits 32]
;.pmode:
;    mov ax,0x10
;    mov ds,ax
;     mov ss,ax
;    mov al,'A'
;    mov ah,0x4f
;    mov [0xb8000],ax
;    cli
;    hlt
KbdControllerDataPort               equ 0x60
KbdControllerCommandPort            equ 0x64
KbdControllerDisableKeyboard        equ 0xAD
KbdControllerEnableKeyboard         equ 0xAE
KbdControllerReadCtrlOutputPort     equ 0xD0
KbdControllerWriteCtrlOutputPort    equ 0xD1
GDT_start:                          ; must be at the end of real mode code
    GDT_null:
        dd 0x0
        dd 0x0

    GDT_code:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10011010
        db 0b11001111
        db 0
    GDT_data:
        dw 0xffff
        dw 0x0
        db 0x0
        db 0b10010010
        db 0b11001111
        db 0
GDT_end:
GDT_descriptor:
    dw GDT_end - GDT_start - 1
    dd GDT_start
CODE_SEG equ GDT_code - GDT_start
DATA_SEG equ GDT_data - GDT_start
BOOT_MSG: db "Entered Stage : booting(16bit)",ENDL,0
DISK_PARA_ERR: db "[ERROR] CAN NOT READ DISK PARAMETERS",ENDL,0
REAL_SECTOR_ERR: db "[ERROR] CAN NOT READ ADVANCED REAL MODE SECTOR(Num : 2). Your Os is broken!",ENDL,0
PROT_MODE_LOCATION: dw 0x7e00
times 510-($-$$) db 0
dw 0xAA55