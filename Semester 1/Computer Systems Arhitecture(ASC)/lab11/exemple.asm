
; the program computes the factorial of a number and writes to the console the result
; the factorial function is defined in the code segment and received on the stack as the parameter a number
bits 32
global start

extern printf, exit
import printf msvcrt.dll
import exit msvcrt.dll

segment data use32 class=data
    format_string db "factorial=%d", 10, 13, 0
    
segment code use32 class=code
; the factorial function
factorial: 
    mov eax, 1
    mov ecx, [esp + 4] 
    ; mov ecx, [esp + 4] pop from the stack the fucntion parameters
    ; ATENTION!!! at the top of the stack it is the retun address
    ; the function's parameter is right after the return address
    ; see the following draw
    ;
    ; stack
    ;
    ;|--------------|
    ;|return address|  <- [esp]
    ;|--------------|
    ;|  00000006h   |  <- the function's parameter, [esp+4]
    ;|--------------|
    ; ....
                
    
    .repeat: 
        mul ecx
    loop .repeat ; atention, the case ecx = 0 is not treated!

    ret
       
; the "main" program       
start:
    push dword 7        ; save on the stack the number (the function's parameter)
    call factorial      ; call the function

       ; write the result
    push eax
    push format_string
    call [printf]
    add esp, 4*2

    push 0
    call [exit]
