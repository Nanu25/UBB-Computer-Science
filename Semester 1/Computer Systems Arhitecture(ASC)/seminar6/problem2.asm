global start
bits 32

extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll
extern append

segment data use32 class = data
    s1 db "Happy"
    l1 equ $ - s1
    s2 db "New year!"
    l2 equ $ - s2
    result times l1 + l2 db 0
    zero db 0
    
segment code use32 class = code public
    start:
        ;append(s1, l1, s2, l2, result)
        ;       (i, i,   i, i,    o)
        ;free memory in main
        
        push result
        push dword l2
        push s2
        push dword l1
        push s1
        call append
        add esp, 4 * 5
        
        ;printf(result)
        push result
        call [printf]
        add esp, 4
    
    push dword 0
    call [exit]
    