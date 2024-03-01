global start

bits 32

extern scanf, fprintf, fopen, fclose, exit
import scanf msvcrt.dll
import fprintf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import exit msvcrt.dll

;Citesc string tastatura, creem fisier string.txt, adaugam in fisier prima data majusculele apoi minusculele invers de cum apar in sir

segment data use32 class = data
    file_name db "string.txt", 0
    write_mode db "w", 0
    fd dd -1
    sir times 30 db 0
    format_str db "%s", 0
    format_c db "%c", 0
segment code use32 class = code

    start:
    ;open the file
    push dword write_mode
    push dword file_name
    call [fopen]
    add esp, 4 * 2
    
    ;check if the open was succesfully
    cmp eax, 0
    je eroare
    mov [fd], eax
    
    push dword sir
    push dword format_str
    call [scanf]
    add esp, 4 * 2
    
    ;uppercase in the order that they appear
    mov esi, sir
    mov ebx, 0
    repeta:
        mov eax, 0
        lodsb   ;actual byte from esi and esi++
        
        cmp al, byte 0
        je end_repeta
        
        cmp al, byte 'A'
        jl not_good
        
        cmp al, byte 'Z'
        jg not_good
        
        push ebx
        
        push dword eax
        push dword format_c
        push dword [fd]
        call [fprintf]
        add esp, 4 * 3
        
        pop ebx
        not_good:
        inc ebx
        jmp repeta
    end_repeta:
    
    mov esi, sir
    
    std ;set direction flag
    dec ebx
    repeta2:
        mov eax, 0
        mov al, [esi + ebx]
        dec ebx
        
        cmp ebx, dword 0
        je end_repeta2
        
        cmp al, 'a'
        jl not_good2
        
        cmp al, 'z'
        jg not_good2
        
        push dword ebx
        
        push dword eax
        push  dword format_c 
        push dword [fd]
        call [fprintf]
        add esp, 4 * 3
        
        pop ebx
        not_good2:
        
    
    jmp repeta2
    end_repeta2:
    
    ;close the file
    push dword [fd]
    call [fclose]
    add esp, 4 * 2
    eroare:
    
    push dword 0
    call [exit]