global start

bits 32

extern scanf, fprintf, exit, fopen, fclose
import scanf msvcrt.dll
import fprintf msvcrt.dll
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll

;A file name and a text (defined in the data segment) are given. The text contains lowercase letters, digits and spaces.
; Replace all the digits on odd positions with the character ‘X’. Create the file with the given name and write
; the generated text to file.

segment data use32 class = data
    file_name db "fis.txt", 0
    accsess_mode db "w", 0
    fd dd -1
    sir times 30 db 0
    format_str db "%s", 0
    new_sir times 30 db 0
    
segment code use32 class = code

    start:
    ;open the file with write format
    push dword accsess_mode
    push dword file_name
    call [fopen]
    add esp, 4 * 2
    
    ;test if the file was open ok
    cmp eax, 0
    je eroare
    mov dword [fd], eax
    
    ;read the file from the keyboard
    push dword sir
    push dword format_str
    call [scanf]
    add esp, 4 * 2
    
    
    mov esi, sir
    mov ecx, 0  ;the current position
    mov edi, new_sir
    repeta:
        lodsb   ;al = byte[esi], esi++
        inc ecx
        
        cmp al, 0   ;end of string
        je end_repeta
        
        ;test if the al is digit
        cmp al, '0'
        jl not_digit
        
        cmp al, '9'
        jg not_digit
        
        ;test if the position is odd
        mov ebx, ecx
        and ebx, 1
        cmp ebx, 1
        jne not_even
        
        mov al, 'X'
        
        not_digit:
        not_even:
        
        stosb
        jmp repeta
        
    end_repeta:
    
    ;print the file
    push dword new_sir
    push dword format_str
    push dword [fd]
    call [fprintf]
    add esp, 4 * 3
        
    eroare:
    
    push dword 0
    call [exit]

