bits 32
global append

segment code use32 class = code public

    append:
        ;stack
        ;esp - return adress(the adress of the next instruction)
        ;esp + 4 - s1
        ;esp + 8 - l1
        ;esp + 12 - s2
        ;esp + 16 - l2
        ;esp + 20 - result
        
        ;copy s1 in result
        mov esi, [esp + 4]
        mov edi, [esp + 20]
        mov ecx, [esp + 8]
        copy1:
            movsb   ;[esi] = byte[edi], esi++, edi++
        loop copy1
        
        ;copy s2 at the end of the result
        mov esi, [esp + 12]
        mov ecx, [esp + 16]
        copy2:
            movsb
        loop copy2
        
        ret