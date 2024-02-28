global start
bits 32

extern exit, printf, fread, fopen, fclose
import exit msvcrt.dll
import printf msvcrt.dll
import fread msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

;Read from file numbers.txt a string of numbers (odd and even). Build two strings using readen numbers:
;P – only with even numbers
;N – only with odd numbers
;Display the strings on the screen.

%include "printstring.asm"

segment data use32 class = data
    new_line db '\n', 0
    format_string db "%s", 0
    format_int db "%d", 0
    in_mode db "r", 0
    file_in db "file.txt", 0
    fd dd -1
    len dd 100
    odd_string times 50 dd 0
    even_string times 50 dd 0
    x times 100 dd 0

segment code use32 class = code

    start:
        
        ;open the file
        push dword in_mode
        push dword file_in
        call [fopen]
        add esp, 4 * 2
        
        cmp eax, 0
        je error1
        mov [fd], eax
        
        mov esi, 0
        mov edi, 0
        
        mov ecx, 0
        repeta:
            push dword [fd]
            push dword 1
            push dword 1
            push dword x
            call [fread]
            add esp, 4 * 4
        
        
            ;mov eax, [x + ecx]
            ;inc ecx
            
            cmp eax, 0
            je repeta_end
            
            
            mov ebx, [x]    ;read a string from the file
            mov edx, ebx    ;move the number to test it s parity
            sub edx, '0'    ;make an int number
            and edx, 1
            cmp edx, 0      
            je par
            
            ;impar 
            mov [odd_string + esi], ebx ;remember the string
            inc esi
            mov [odd_string + esi], " "
            inc esi
            jmp continue
        
            par:
               mov [even_string + edi], ebx
               inc edi
            continue:
        jmp repeta
        
        repeta_end:
        
        ;cllose the file
        push dword [fd]
        call [fclose]
        add esp, 4 * 1
        
        
        
        push dword format_int
        push dword esi
        push dword odd_string
        call print_string
        
        push dword new_line
        push dword format_string
        call [printf]
        add esp, 4 * 2
        
        push dword format_int
        push dword edi
        push dword even_string
        call even_string
        
        
        ;display the odd numbers
        ;mov ecx, esi
        ;mov eax, 0      ;the index
        ;mov esi, odd_string
        ;jecxz end_loop1
        ;start_loop1:
        ;    mov ebx, 0
        ;    mov bl, [esi + eax]
        ;    inc eax
            
        ;    sub ebx, '0'
            
            
        ;    pusha
            
        ;    push dword  ebx
        ;    push dword format_int
        ;    call [printf]
        ;    add esp, 4 * 2
            
        ;    popa
        ;loop start_loop1
        ;end_loop1:

        
        error1:
        
    push dword 0
    call [exit]