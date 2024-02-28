bits 32
global start

extern exit, fread, fopen, fclose, fwrite, perror
import fopen msvcrt.dll
import exit msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll
import fwrite msvcrt.dll
import perror msvcrt.dll


segment data use32 class = data

;read from a file and display the caracter + 1 in another file

    file_in db "file.txt", 0
    file_out db "file_out.txt", 0
    in_mode db "r", 0
    out_mode db "w", 0
    fd_in dd -1
    fd_out dd -1
    c db 0
    eroare db "Eroare", 0

segment code use32 class = code

    start:
    
    ;deschid fisierul
    push dword in_mode
    push dword file_in
    call [fopen]
    add esp, 4 * 2
    
    cmp eax, 0
    je error1
    mov [fd_in], eax
    
    push dword out_mode
    push dword file_out
    call [fopen]
    add esp, 4 * 2
    
    cmp eax, 0
    je error2
    
    mov [fd_out], eax
    repeta:
        push dword [fd_in]
        push dword 1    ;size of char
        push dword 1    ;numarul de caractere
        push dword c
        call [fread]
        add esp, 4 * 4
        
        cmp eax, 0
        je repeta_end
        
        add byte [c], 1
        
        push dword [fd_out]
        push dword 1
        push dword 1
        push dword c
        call [fwrite]
        add esp, 4 * 4
        
        jmp repeta
        
        
    repeta_end:
    
    push dword [fd_out]
    call [fclose]
    add esp, 4 * 1
    
    error2:
    push dword eroare
    call [perror]
    add esp, 4 * 1
    
    error1:
    push dword eroare
    call [perror]
    add esp, 4 * 1
    
    push dword 0
    call [exit]