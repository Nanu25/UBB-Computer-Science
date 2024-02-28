bits 32
global bubble_sort

segment code use32 class = code public

    bubble_sort:
        ;esp + 4 -> offset of the array
        ;need to sort the array
        mov esi, [esp + 4]
        mov bl, 1
        repeta:
            mov bl, 0
            mov ecx, 5
            dec ecx         ;minus the last element
            jecxz loop_end1
                
            mov edi, 0  ;index from the iteration
            loop_sort:
                mov edx, [esi + edi]        ;edx = [esi + edi]   
                mov eax, [esi + edi + 4]    ;eax = [esi]
                
                cmp edx, eax
                jle not_swap
                
                ;swap the values if edx > eax
                push dword eax
                mov eax, edx
                pop edx
                mov bl, 1   ;one mote step in loop
                
                not_swap:
                                
                ;edx is lower than eax
                mov [esi + edi], edx        ;update the array from the memory
                mov [esi + edi + 4], eax
                add edi, 4
                
            loop loop_sort
            
            cmp bl, byte 1
            je repeta
            loop_end1:
    ret 4