global start

bits 32

extern printf, exit, fread, fopen, fclose
import printf msvcrt.dll
import exit msvcrt.dll
import fread msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

;A text file is given. Read the content of the file, determine the digit with the highest frequency 
;and display the digit along with its frequency on the screen. The name of text file is defined in the data segment.

segment data use32 class = data
    file_name db "fisier.txt", 0
    access_mode db "r", 0
    format_int db "%d", 0
    fd dd -1
    len equ 20
    sir times len db 0
    lungime dd 0
    apmax db 0
    cifra db 0
    space db " ", 0

segment code use32 class = code

    start:
        ;open the file
        push dword access_mode
        push dword file_name
        call [fopen]
        add esp, 4 * 2
        
        ;test if we open the file well
        cmp eax, 0
        je eroare
        mov [fd], eax
        
        ;read from the file
        push dword [fd]
        push dword len  ;how many caracters we read
        push dword 1    ;size of the caracters
        push dword sir  ;offset of the string
        call [fread]    ;in eax we have the lenght of the string
        add esp, 4 * 4
        
        ;eax = the lenght of the string we read
        mov [lungime], eax    ;the lenght of the string
        
        mov eax, 0      ;for the stosb
        mov esi, sir
        repeta:
            lodsb   ;take every byte
            
            cmp al, 0       ;end of the string
            je end_repeta
            
            ;test if the actual byte is a digit
            cmp al, '0'
            jl nu_e_cifra
            
            cmp al, '9'
            jg nu_e_cifra
            
            ;count the number of apparence
            mov edi, sir
            mov ecx, [lungime]    ;lenght of the string
            mov ebx, 0      ;the index from the new string
            mov dh, 0       ;number of apparence
            jecxz end_repeta
            start_loop:
                mov dl, byte [edi + ebx]    ;the current letter
                inc ebx
                
                cmp al, dl
                jne mai_departe
                add dh, byte 1
                
                mai_departe:
                loop start_loop
            
            cmp dh, byte [apmax]
            jle move_on
            mov [apmax], dh
            mov [cifra], al
            
            nu_e_cifra:
            move_on:
            jmp repeta
            
        end_repeta:
        
        ;close the file
        push dword [fd]
        call [fclose]
        add esp, 4 * 1
        
        ;make the digit int
        sub [cifra],byte  '0'
        
        mov eax, 0  ;mov the digit into eax
        mov al, byte [cifra]
        
        push dword eax
        push dword format_int
        call [printf]
        add esp, 4 * 2
        
        push dword space
        call [printf]
        add esp, 4 * 1
        
        mov eax, 0
        mov al, [apmax] ;move the number of apparence to eax
        
        push dword eax
        push dword format_int
        call [printf]
        add esp, 4 * 2
        
        eroare:
    
    push dword 0
    call [exit]