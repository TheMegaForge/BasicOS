[bits 32]
%include "asm_include/utils/StackDef.inc"
global putText
; -- arguments --
; esi = string source
; edi = text address to put the string in
; cl = color
; -- return --
; edx = edi+characters written
; cx = written characters
putText:
  push eax
  push ebx
  initStack 8
  mov [ebp-4],dword 0 ;incremented bytes for string
  mov [ebp-8],dword 0 ;incremented bytes for buffer
  .Tloop:
    xor ebx,ebx
    xor eax,eax
    mov ebx,[ebp-4]
    mov al,[esi+ebx]  ;gets char

    mov ah,cl
    mov ebx,[ebp-8]
    mov [edi+ebx],ax  ;prints char to screen

    inc dword [ebp-4]   ;increments
    add dword [ebp-8],2
    mov ebx,[ebp-4]
    add ebx,esi
    cmp [ebx],byte 0
    je .TEnd        ;checks if '\0'
    
    jmp .Tloop
  .TEnd:
    xor ecx,ecx
    mov cx,[ebp-4]
    mov edx,[ebp-8]
    add edx,edi
  clearStack 8
  pop eax
  pop ebx
  ret
global newLine
;-- Arguments --
;cx = already chars written
;edx = text address
;bl = color
;-- return value --
;cx = characters needed to fill the line
;edx = new text address
newLine:
  push eax
  push esi
  initStack 4
  mov [ebp-4],word 80 ;80 - cx
  sub [ebp-4],cx
  mov [ebp-2],word 0  ;incremented address
  cmp word [ebp-4],0
  jz .NEnd
  .NLoop:
    xor eax,eax
    xor esi,esi         ;resets tmps
    dec word [ebp-4]    ;counter--
    mov al,' '
    mov ah,bl
    mov si,[ebp-2]      ;stores advanced address into si
    mov [edx+esi],ax    ;loads character
    add [ebp-2],word 2  ;address+=2
    cmp [ebp-4],word 0  ;return if counter == 0
    jnz .NLoop
  .NEnd:
    xor eax,eax     ;ensures 
    mov cx,[ebp-2]  
    push edx
    xor edx,edx
    mov ax,cx
    mov cx,2
    div cx        ;address/2
    xor cx,cx
    mov cx,ax     ;stores result in cx
    pop edx
    add dx,word [ebp-2]
  clearStack 4
  pop esi
  pop eax
  ret
global setScreenColor
;
;cl = color
;
setScreenColor:
  push eax
  push ebx
  push edx
  push esi
  xor esi,esi
  xor edx,edx
  mov eax,80
  mov ebx,25
  mul ebx
  mov edx,eax
  .SLoop:
    dec edx
    mov al,' '
    mov ah,cl
    mov [0xb8000+esi],ax
    add esi,2
    cmp edx,0
    jnz .SLoop
  .SEnd:

  pop esi
  pop edx
  pop ebx
  pop eax
  ret