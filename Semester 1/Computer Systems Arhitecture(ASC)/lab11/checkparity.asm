%ifndef _CHECKPARITYASM_
%define _CHECKPARITYASM_

Check_parity:

    mov eax, [esp + 4]  ;numarul pe care l testez
    and eax, 1
    ret 4
%endif
    