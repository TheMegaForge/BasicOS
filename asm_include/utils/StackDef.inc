%macro initStack 1
    push ebp
    mov ebp,esp
    sub esp,%1
%endmacro
%macro clearStack 1
    add esp,%1
    mov esp,ebp
    pop ebp
%endmacro
;
; 1 = register to store in
; 2 = type
; 3 = size
