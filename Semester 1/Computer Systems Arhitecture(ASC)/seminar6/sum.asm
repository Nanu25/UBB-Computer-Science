bits 32
global sum

segment code use32 class = code public
    sum:
        ;sum(a, b) - return a + b in eax
        ;push parameterson the stack in reverse order
        ;free memory in the procedure   
        
        ;stack
        ;esp - return adress
        ;esp + 4 - value of a
        ;esp + 8 - value of b
        
        mov eax, [esp + 4]
        add eax, [esp + 8]
        
        ret 4 * 2   ;2 parametrii