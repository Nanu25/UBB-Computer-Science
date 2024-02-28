bits 32
global start

extern exit, scanf, printf
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class = data
   
   print_message1 db "Give the first number", 13, 10, 0
   format_int db "%d", 0
   print_message2 db "Give the second numner", 13, 10, 0
   print_message3 db "The sum of the numbers", 13, 10, 0
   n dd 0
   m dd 0
   s dd 0


segment code use32 class = code

    start:
    push dword print_message1
    call [printf]
    add esp, 4 * 1
    
    push dword n
    push dword format_int
    call [scanf]
    add esp, 4 * 2
    
    push dword print_message2
    call [printf]
    add esp, 4 * 1
    
    push dword m
    push dword format_int
    call [scanf]
    add esp, 4 * 2
    

    push dword print_message3
    call [printf]
    add esp, 4 * 1
    
    
    mov eax, [n]
    add eax, [m]
        
    push dword eax
    push dword format_int
    call [printf]
    add esp, 4 * 2
    
    
    
    
    push dword 0
    call [exit]