global start

bits 32


extern fscanf, printf, fopen, fclose, exit
import fscanf msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import exit msvcrt.dll

;1.	Se dă un șir de 10 numere în baza 16 în fișierul input.txt. 
;Să se determine cifra minimă din fiecare număr.
;Să se afișeze acest șir al cifrelor minime, în baza 10, pe ecran.


segment data use32 class = data
    file_name db "input.txt", 0
    read_mode db "r", 0
    fd dd -1
    x dd 0
    sir times 10 dd 0
    format_hexa db "%X", 0
    format_int db "%d ", 0
    zece dd 10

segment code use32 class = code

    start:
    ;open the file
    push dword read_mode
    push dword file_name
    call [fopen]
    add esp, 4 * 2
    
    ;check if the file was open corect
    cmp eax, 0
    je eroare
    mov [fd], eax
    
    mov ecx, dword 10   ;number of dwords i read
    mov edi, sir        ;sirul de cifre minime
    start_loop:
    
        ;read the number
        pusha
        
        ;read the number in hexa format
        push dword x
        push dword format_hexa
        push dword [fd]
        call [fscanf]
        add esp, 4 * 3
        
        popa
        
        ;store the number in eax
        mov eax, dword [x]
        mov ebx, 10  ;cifra minima
        repeta:
           cmp eax, 0
           je end_repeta
           
           mov edx, dword 0 ;to make the division on edx:eax
           div dword [zece]
           
           ;edx will be the last digit of eax, and eax /= 10.
           cmp edx, ebx
           jg not_good
           mov ebx, edx
           
           not_good:
           jmp repeta
           
        end_repeta:
        mov eax, ebx
        stosd   ;keep the minimum digit of the actual number
        
    loop start_loop
    
    mov esi, sir
    mov ecx, dword 10
    loop_start1:
    lodsd   ;actual dd which is a digit
    pusha
    
    push dword eax
    push dword format_int
    call [printf]
    add esp, 4 * 2
    
    popa
    
    loop loop_start1
    
    push dword [fd]
    call [fclose]
    add esp, 4 * 1
    
    eroare:
    
    push dword 0
    call [exit]