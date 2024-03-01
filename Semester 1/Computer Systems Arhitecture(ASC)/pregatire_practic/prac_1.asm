global start

bits 32

extern scanf, printf, exit, fread, fopen, fclose
import scanf msvcrt.dll
import printf msvcrt.dll
import exit msvcrt.dll
import fscanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll

;a file name is read from the keyboard and a integer number N. The program
;will read from the file and make the sum of the n'th bite from every number

segment data use32 class = data
    file_name times 20 db 0 
    read_mode db 'r', 0
    fd dd -1
    format_str db "%s", 0
    n dd -1
    format_int db "%d", 0
    sir times 50 db 0
    len equ 50
    

segment code use32 class = code

    start:
    ;read the file name from the keyboard
    push dword file_name
    push dword format_str
    call [scanf]
    add esp, 4 * 2
    
    ;open the file
    push dword read_mode
    push dword file_name
    call [fopen]
    add esp, 4 * 2
    
    ;check if i have an error
    cmp eax, 0
    je eroare
    mov [fd], eax
    
    ;read n from the keyboard
    push dword n
    push dword format_int
    call [scanf]
    add esp, 4 * 2
    
    ;call the fread function
    push dword [fd]
    push dword len
    push dword 1
    push dword sir
    call [fread]
    add esp, 4 * 4
    
    mov esi, sir
    mov ecx, eax    ;lenght of the file
    mov eax, 0  ;where i load the bytes
    mov ebx, 0  ;sum of the bits
    jecxz end_loop
    
    start_loop:
        lodsb   ;the actual byte
        
        sub al, byte '0'        ;find it's value
        
        ;make the shift with ecx
        push ecx
        
        mov ecx, dword [n]
        
        shr al, cl
        and al, byte 1
        
        add bl, al
        
        pop ecx     ;value for the loop
    loop start_loop
    
    end_loop:
   
    ;print the sum on the screen
    push dword ebx
    push dword format_int
    call [printf]
    add esp, 4 * 2
   
    push dword [fd]
    call [fclose]
    add esp, 4 * 1

    eroare:
    
    
    push dword 0
    call [exit]