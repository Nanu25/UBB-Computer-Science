global start
bits 32

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll
extern sum
segment data use32 class = data
    a dd 13
    b dd 14
    format db " %d + %d = %d", 13, 10, 0

segment code use32 class = code public

    start:
        ;sum(a, b) - return a + b in eax
        ;push parameterson the stack in reverse order
        ;free memory in the procedure
        push dword [b]
        push dword [a]
        call sum
        ;in eax we'll have the sum
        
        ;printf(%d + %d = %d, a, b, eax)
        push eax
        mov ebx, 0
        mov bl, [a]
        mov ecx, 0
        mov cl, [b]
        push dword ebx
        push dword ecx
        push format
        call [printf]
        add esp, 4 * 4
    
    
    push dword 0
    call [exit]
    