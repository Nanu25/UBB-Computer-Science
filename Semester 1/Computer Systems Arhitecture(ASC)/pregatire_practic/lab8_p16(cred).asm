global start 

bits 32

extern fread, fopen, fclose, printf, exit
import fread msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import exit msvcrt.dll

;A text file is given. Read the content of the file, count the number of letters 'y' and 'z' and
; display the values on the screen. The file name is defined in the data segment.

segment data use32 class = data

    file_name db "fis2.txt", 0
    read_mode db "r", 0
    fd dd -1
    sir times 50 db 0
    len dd 40
    format_int_y db "numarul de y= %d ", 0
    format_int_z db "numarul de z= %d ", 0
    format_str db "%s", 0
    new_line db 10
    
segment code use32 class = code

    start:
    
    ;open the file in read mode
    push dword read_mode
    push dword file_name
    call [fopen]
    add esp, 4 * 2
    
    ;test if the file was open right
    cmp eax, 0
    je eroare
    mov [fd], eax
    
    ;read the string from the file
    push dword [fd]
    push dword [len]
    push dword 1
    push dword sir
    call [fread]
    add esp, 4 * 4
    
    ;check if i read the correct string
    ;push dword sir
    ;push dword format_str
    ;call [printf]
    ;add esp, 4 * 2
    
    ;eax hsve the lenght of the file
    mov esi, sir
    mov dx, word 0  ;dl - number of y, dh - number of z
    repeta:
        lodsb   ;al it s the actual letter from esi, esi++
        
        cmp al, 0
        je end_repeta
        
        cmp al, byte 'z'
        jne not_good
        add dh, byte 1
        
        not_good:
        cmp al, byte 'y'
        jne not_good1
        
        add dl, byte 1
        
        not_good1:
        jmp repeta
        
    end_repeta:
    
    mov eax, 0
    mov al, dl
    push edx        ;to save the values of number of y and z
    
    ;print the number of y
    push dword eax
    push dword format_int_y
    call [printf]
    add esp, 4 * 2
    
    ;print new line
    push dword new_line
    push dword format_str
    call [printf]
    add esp, 4 * 2
    
    pop edx
    
    ;print the number of z
    mov eax, 0
    mov al, dh
    push dword eax
    push dword format_int_z
    call [printf]
    add esp, 4 * 2
    
    push dword [fd]
    call [fclose]
    add esp, 4
    
    eroare:
    
    
    push dword 0
    call [exit]