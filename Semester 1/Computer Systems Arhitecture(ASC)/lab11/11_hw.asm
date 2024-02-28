global start

bits 32

extern scanf, printf, exit
import printf msvcrt.dll
import exit msvcrt.dll
import scanf msvcrt.dll

;Multiple numbers in base 2 are read from the keyboard. Display these numbers in the base 16.

%include "convertbase10.asm"

segment data use32 class = data
    n dd 0
    message_input db "The number of strings to read ", 0
    
    format_int db "%d", 0
    format_str db "%s", 0
    number times 31 db 0
    output db 'the number in base 16 = %x', 0
    
segment code use32 class = code

    start:
       push message_input   ;the message from the begin
       call [printf]
       add esp, 4 * 1
       
       push dword n         ;numer of strings
       push dword format_int
       call [scanf]
       add esp, 4 * 2
      
       mov ecx, [n]         ;how many reads i need to perform
       jecxz final
       loop1:
           pusha        ;push the registers on the stack
           
           push dword number        ;read the numbers by string format
           push dword format_str
           call [scanf]
           add esp, 4 * 2
           
           push  number ;pun adresa stringului pe stiva
           call convert_base_10
           
           push eax             ;here is the number in base 10
           push dword output
           call [printf]
           add esp, 4 * 2
           
           popa
       loop loop1
      
        final:
    
    push dword 0
    call [exit]
