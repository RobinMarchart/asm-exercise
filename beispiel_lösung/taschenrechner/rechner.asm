    section .rodata
    ;; read only not executable data
_rechner_jmp_tbl:
    dd rechner_const_asm
    dd rechner_add_asm
    dd rechner_sub_asm
    dd rechner_mul_asm
    
    section .text
    ;; read only executable data

    global rechner_const_asm
    global rechner_add_asm
    global rechner_sub_asm
    global rechner_mul_asm
    global rechner_sel_asm

rechner_const_asm:
    mov eax, [ebx]
    and eax, 0xfffffff8
    sar eax, 3
    pop ebp
    ret

rechner_add_asm:
    push ebx
    mov ebx, [ebx + 4]
    push ebx
    call rechner_sel_asm
    add esp, 4
    cmp edx, 0
    jz .eval_1
    mov edx, 1
    add esp, 4
    pop ebp
    ret
    .eval_1:    
    pop ebx
    mov ebx, [ebx + 8]
    push ebx
    mov ebx, eax
    call rechner_sel_asm
    add esp, 4
    cmp edx, 0
    jz .eval_2
    mov edx, 1
    pop ebp
    ret
    .eval_2:
    add eax, ebx
    jo .eval_3
    mov edx, 1
    .eval_3:
    pop ebp
    ret

rechner_sub_asm:
    push ebx
    mov ebx, [ebx + 4]
    push ebx
    call rechner_sel_asm
    add esp, 4
    cmp edx, 0
    jz .eval_1
    mov edx, 1
    add esp, 4
    pop ebp
    ret
    .eval_1:    
    pop ebx
    mov ebx, [ebx + 8]
    push ebx
    mov ebx, eax
    call rechner_sel_asm
    add esp, 4
    cmp edx, 0
    jz .eval_2
    mov edx, 1
    pop ebp
    ret
    .eval_2:
    sub eax, ebx
    jo .eval_3
    mov edx, 1
    .eval_3:
    pop ebp
    ret

rechner_mul_asm:
    push ebx
    mov ebx, [ebx + 4]
    push ebx
    call rechner_sel_asm
    add esp, 4
    cmp edx, 0
    jz .eval_1
    mov edx, 1
    add esp, 4
    pop ebp
    ret
    .eval_1:    
    pop ebx
    mov ebx, [ebx + 8]
    push ebx
    mov ebx, eax
    call rechner_sel_asm
    add esp, 4
    cmp edx, 0
    jz .eval_2
    mov edx, 1
    pop ebp
    ret
    .eval_2:
    imul eax, ebx
    jo .eval_3
    mov edx, 1
    .eval_3:
    pop ebp
    ret

rechner_sel_asm:
    push ebp
    mov ebp, esp
    mov ebx, [ebp + 8]
    mov eax, [ebx]
    and eax, 0x07
    jmp [_rechner_jmp_tbl + eax * 4]
    
