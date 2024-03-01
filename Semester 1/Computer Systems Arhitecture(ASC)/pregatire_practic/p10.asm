global start

bits 32


extern exit, scanf, fprintf, fopen, fclose
import exit msvcrt.dll
import scanf msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll 

;Se citeste de la tastatura m,n apoi m numere zecimale, pe linii diferite.
; Sa se afiseze nr cu cel putin n cifre pare in output.txt

segment data use32 class = data

    file_name db "output.txt", 0
    write_mode db "w", 0
    fd dd -1
    format_int db "%d ", 0
    n dd 0
    m dd 0
    x dd 0
    cifre_pare dd 0
    zece dd 10
    
segment code use32 class = code

    start:
        ;open the file
        push dword write_mode
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        ;test if it was open corect
        cmp eax, 0
        je eroare
        mov dword [fd], eax
        
        ;read m
        push dword m
        push dword format_int
        call [scanf]
        add esp, 4 * 2
        
        ;read n
        push dword n
        push dword format_int
        call [scanf]
        add esp, 4 * 2
        
        mov ecx, dword [m]
        jecxz loop_end
        loop_start:
            pusha
            
            ;read the actual number
            push dword x
            push dword format_int
            call [scanf]
            add esp, 4 * 2
            
            ;count the even digits of x
            mov eax, dword [x]
            mov [cifre_pare], dword 0
            repeta:
                
                cmp eax, 0      ;end of the number
                je end_repeta
                
                mov ebx, eax    ;copy for the actual number
                and eax, 1      ;test if the digit is even
                cmp eax, dword 0
                jne not_even
                
                add [cifre_pare], dword 1
                
                not_even:
                
                mov eax, ebx
                mov edx, 0
                div dword [zece]    ;erase the digit
            jmp repeta
            
            end_repeta:
            
            mov eax, dword [cifre_pare]
            cmp eax, dword [n]
            jl mai_departe
            
            ;print the number if it has minim n even digits
            push dword [x]
            push dword format_int
            push dword [fd]
            call [fprintf]
            add esp, 4 * 3
            
            mai_departe:
            popa
        
        loop loop_start
        loop_end:
        
        ;close the file
        push dword [fd]
        call [fclose]
        add esp, 4 * 2
        
        eroare:
    
    push dword 0
    call [exit]