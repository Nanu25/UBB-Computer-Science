global start

bits 32

extern scanf, fprintf, fopen, fclose, exit
import scanf msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import exit msvcrt.dll

;A byte string s is given(read n numbers from console). Build the byte string  
;d such that every byte d[i] is equal to the count of ones in the corresponding byte s[i] of s.

segment data use32 class = data
    file_name db "fis3.txt", 0
    write_mode db "w", 0
    fd dd -1
    s times 20 dd 0
    d times 20 dd 0
    n dd 0
    x dd 0
    format_int db " %d", 0
    

segment code use32 class = code

    start:
        ;open the file
        push dword write_mode
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        ;test if the file was open succefully
        cmp eax, dword 0
        je eroare
        mov [fd], eax
        
        ;read the number n
        push dword n
        push dword format_int
        call [scanf]
        add esp, 4 * 2
        
        mov ecx, dword [n]
        mov edi, s
        jecxz end_loop
  
        start_loop:
        
        pusha   ;store all the registers
        
        push dword x
        push dword format_int
        call [scanf]
        add esp, 4 * 2
       
        popa    ;restore the registers
        
        ;store the value
        mov eax, dword [x]
        stosd   ;edi = eax, edi++;
        
        loop start_loop
        
        mov esi, s
        mov ecx, dword [n]
        mov edi, d
        ;nu mai pun jecxz pentru ca s ar fii executat prima data
        loop_start1
            lodsd   ;eax = esi, esi++
            
            ;count the number of 1 in the eax reprezentation
            mov edx, 0
            repeta:
                mov ebx, eax
                cmp ebx, dword 0
                je end_repeta
                
                and ebx, 1
                add edx, ebx    ;if ebx = 1 then i add a new bite in the total number of bits
                
                shr eax, 1
                jmp repeta
                
            end_repeta:
        
            mov eax, edx
            stosd       ;edi = eax, edi++
        
        loop loop_start1
        end_loop:
        
        ;print the new array in the file
        mov esi, d
        mov ecx, dword [n]
        start_loop2:
        
        lodsd   ;eax = esi, esi++
        pusha
        
        push dword eax
        push dword format_int
        push dword [fd]
        call [fprintf]
        add esp, 4 * 3
        
        
        popa
        loop start_loop2
       
        eroare:
        
        
    
    push dword 0
    call [exit]
