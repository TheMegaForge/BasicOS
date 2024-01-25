global setBit
;
;-- Arguments --
;eax = number
;cl = pos
;-- Return --
;eax = number
setBit:
    push edx
    dec cl
    mov edx,1   ;shift number
    shl edx,cl  ;shift count
    or eax,edx  ;adding byte
    pop edx
    ret
global removeBit
;
;
;eax = number
;cl = pos
;-- Return --
;eax = number
removeBit:
    push edx
    dec cl
    mov edx,1
    shl edx,cl
    not edx
    and eax,edx
    pop edx
    ret
