%ifndef _CONVERTBASE10ASM_
%define _CONVERTBASE10ASM_

convert_base_10:
	mov ebx, [esp + 4]; ebx = adresa sirului de biti
    mov esi, 0
    mov eax, 0; aici vom tine suma
    mov ecx, 0; loop luuung
    .repeta:
        mov edx, 0; pentru a converti bitul la reprezentare pe doubleword
        mov dl, [ebx + esi]
        cmp dl, 0
        je end_loop
        
        push edx; salvam edx
        
        mov edx, 2
        mul edx; eax = eax * 2 pentru ca urmeaza sa adaugam un nou bit (suportam maxim 32 de biti)
        
        pop edx; restauram edx
        
        add eax, edx
        sub eax, '0'; eax = eax + 1(daca bitul este 1) sau ramane neschimbat(daca bitul este 0)
        inc esi; trecem la urmatorul caracter
    loop .repeta
    end_loop:
	ret 4
%endif