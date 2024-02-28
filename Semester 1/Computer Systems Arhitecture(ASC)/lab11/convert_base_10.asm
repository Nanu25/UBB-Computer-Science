%ifndef _CONVERT_BASE_10_ASM_
%define _CONVERT_BASE_10_ASM_

convert_base_10:

    mov eax, 1          ;puterea lui 2 corespunzatoare
    mov esi, 0          ;indicele din sir
    mov ebx, [esp + 4]  ;sirul
    mov ecx, 0          ;pentru un loop lung
    mov edi, 0          ;rezultatul
    
    start_conversion:
        mov edx, 0      ;am un bit si vreau sa l transform in dd
        mov dl, [ebx + esi] ;bitul actual
        cmp edx, 0          ;conditia de iesire
        je end_conversion
       
       sub edi, '0'         ;il transform in int
       cmp edi, 0           ;daca e 0 nu l adun la suma
       je continue
    
       add edi, eax ;adun la rezultat
       
       continue:
       shl eax, 1       ;eax = eax * 2
       inc esi          ;urmatorul bit
    loop start_conversion
 
    end_conversion:
    mov eax, edi    ;retin rezultaul in eax
    ret 4

%endif