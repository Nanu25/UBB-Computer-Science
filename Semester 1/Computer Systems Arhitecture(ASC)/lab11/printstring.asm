%ifndef _PRINTSTRINGASM_
%define _PRINTSTRINGASM_

extern printf
import printf msvcrt.dll

print_string:
    mov edi, [esp + 4]  ;format int
    add esp, 4 * 1
    
    mov ecx, [esp + 4]  ;the lenght of the string
    add esp, 4 * 1
    
    mov esi, [esp + 4]  ;the offset of the string
    mov eax, 0
    jecxz end_loop
    start_loop:
        mov ebx, 0
        mov bl, [esi + eax]
        inc eax
        sub ebx, '0'
        
        pusha
        push dword ebx
        push dword edi
        call [printf]
        popa

    
    loop start_loop
    
    end_loop:
    ret 4 * 3
%endif