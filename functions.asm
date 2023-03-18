section .data
    one dq 1.0
    two dq 2.0
    three dq 3.0

section .text

global f1
global f2
global f3

extern exp

f1:
    push ebp
    mov ebp, esp
    finit
    fld qword[one]
    push dword[ebp + 12]
    push dword[ebp + 8]
    call exp
    fdivp
    fld qword[three]
    faddp
    mov esp, ebp
    pop ebp
    ret

f2:
    push ebp
    mov ebp, esp
    finit
    fld qword[two]
    fld qword[ebp + 8]
    fmulp
    fld qword[two]
    fsubp
    mov esp, ebp
    pop ebp
    ret

f3:
    push ebp
    mov ebp, esp
    finit
    fld qword[one]
    fld qword[ebp + 8]
    fdivp
    mov esp, ebp
    pop ebp
    ret
