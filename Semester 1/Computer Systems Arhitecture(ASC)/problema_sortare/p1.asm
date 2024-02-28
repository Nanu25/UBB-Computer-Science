global start

bits 32

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
extern bubble_sort

;am un vector citit de la tastatura. Daca are lungimea variabila(diferita de 5) nu merge modulul
;daca nu folosesc modul merge pentru orice dimensiune. Programul afiseaza vectorul sortat crescator.

segment data use32 class = data public

    n dd 0
    x dd 0
    arr times 20 db 0
    format_int db "%d", 0
    output_format db "%d ", 0

segment code use32 class = code public

    start:
        ;read the number of elements
        push dword n
        push dword format_int
        call [scanf]
        add esp, 4 * 2
        
        mov ecx, [n]
        jecxz end_loop
        mov edi, arr
        start_loop:
            pushad
            
            ;read the value from the array
            push dword x
            push dword format_int
            call [scanf]
            add esp, 4 * 2
            
            popad
            
            ;store the value
            mov eax, dword [x]
            stosd   ;edi = eax, edi+=4.
        loop start_loop
        end_loop:
        
        ;the parameter needs to be the array offset
        push dword arr
        call bubble_sort
        
        ;need to sort the array
        ;mov esi, arr
        ;mov bl, 1
        ;repeta:
            ;mov bl, 0
            ;mov ecx, [n]    ;lenght of the array
            ;dec ecx         ;minus the last element
            ;jecxz loop_end1
                
            ;mov edi, 0  ;index from the iteration
            ;loop_sort:
                ;mov edx, [esi + edi]        ;edx = [esi + edi]   
                ;mov eax, [esi + edi + 4]    ;eax = [esi]
                
                ;cmp edx, eax
                ;jle not_swap
                
                ;swap the values if edx > eax
                ;push dword eax
                ;mov eax, edx
                ;pop edx
                ;mov bl, 1   ;one mote step in loop
                
                ;not_swap:
                                
                ;edx is lower than eax
                ;mov [esi + edi], edx        ;update the array from the memory
                ;mov [esi + edi + 4], eax
                ;add edi, 4
                
            ;loop loop_sort
            
            ;cmp bl, byte 1
            ;je repeta
            ;loop_end1:
    
        ;try to print to the screen the array
        mov ecx, [n]
        jecxz loop_end2
        mov esi, arr
        
        print_loop:
        lodsd   ;eax = [esi], esi += 4
        
        pushad
        push eax
        push dword output_format
        call [printf]
        add esp, 4 * 2
        popad
        
        loop print_loop
        
        loop_end2:
    
    
    push dword 0
    call [exit]