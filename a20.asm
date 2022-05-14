; Enable and disable A20

BITS 16

section .text

enable_msg:  db 'Enabling A20........'
enable_len   equ $ - enable_msg

disable_msg: db 'Disabling A20......'
disable_len  equ $ - disable_msg

check_msg:   db 'Checking A20.........'
check_len    equ $ - check_msg

ok_msg:      db 'OK!'
ok_len       equ $ - ok_msg

fail_msg:    db 'FAIL!'
fail_len     equ $ - fail_msg

contadorlineas: dw 0x0000

; Print string in real mode
;
; Parametros:
;       %1      Message
;       %2      Length
;       %3      Color
;       %4      Row
;       %5      Column
%macro REAL_MODE_PRINT 5
    pusha
    push    es
    mov     ax, 0xB800          ;Video segment
    mov     es, ax
    %if %4 <> dx
    mov     dx, %4
    %endif
    cmp     dx, 0xFFFF
    je      %%sigo
    add     WORD [contadorlineas], 0x0001
    %%sigo:
    mov     ax, [contadorlineas]
    mov     bx, 80
    mul     bx
    mov     bx, ax
    %if %5 <> dx
    mov     dx, %5  ;offset
    %endif

    add     bx, dx
    shl     bx, 1
    %if %1 <> di
    mov     di, %1          
    %endif
    %if %2 <> cx
    mov     cx, %2          
    %endif
    %if %3 <> ah
    mov     ah, %3          
    %endif
        %%ciclo_cadena:
        mov     al, [di]            
        mov     [es:bx], ax         
        add     bx, 2
        inc     di
        loop    %%ciclo_cadena

    pop     es
    popa
%endmacro

A20_disable:
    pushf
    pusha
    REAL_MODE_PRINT disable_msg, disable_len, 0x07, 0, 0
    call    A20_wait
    mov     al,0xAD
    out     0x64,al
    call    A20_wait
    mov     al,0xD0
    out     0x64,al
    call    A20_wait2
    in      al,0x60
    push    ax
    call    A20_wait
    mov     al,0xD1
    out     0x64,al
    call    A20_wait
    pop     ax
    and     al,0xFD     ;deshabilito
    out     0x60,al
    call    A20_wait
    mov     al,0xAE
    out     0x64,al
    call    A20_wait
    REAL_MODE_PRINT ok_msg, ok_len, 0x0A, 0xFFFF, 23
    popa
    popf
    ret


A20_enable:
    pushf
    pusha
    REAL_MODE_PRINT enable_msg, enable_len, 0x07, 0, 0
    call    A20_wait
    mov     al,0xAD
    out     0x64,al
    call    A20_wait
    mov     al,0xD0
    out     0x64,al
    call    A20_wait2
    in      al,0x60
    push    ax
    call    A20_wait
    mov     al,0xD1
    out     0x64,al
    call    A20_wait
    pop     ax
    or      al,2
    out     0x60,al
    call    A20_wait
    mov     al,0xAE
    out     0x64,al
    call    A20_wait
    REAL_MODE_PRINT ok_msg, ok_len, 0x0A, 0xFFFF, 23
    popa
    popf
    ret
    
A20_wait:
    in      al,0x64
    test    al,2
    jnz     A20_wait
    ret

A20_wait2:
    in      al,0x64
    test    al,1
    jz      A20_wait2
    ret

A20_check:
    pushf
    push fs
    push gs
    push di
    push si
    REAL_MODE_PRINT check_msg, check_len, 0x07, 0, 0
    xor ax, ax ; ax = 0
    mov fs, ax
    not ax ; ax = 0xFFFF
    mov gs, ax
    mov di, 0x0500
    mov si, 0x0510
    mov al, byte [fs:di]
    push ax
    mov al, byte [gs:si]
    push ax
    mov byte [fs:di], 0x00
    mov byte [gs:si], 0xFF
    cmp byte [fs:di], 0xFF
    je .falla
        REAL_MODE_PRINT ok_msg, ok_len, 0x0A, 0xFFFF, 23
    jmp .sigue
    .falla:
        REAL_MODE_PRINT fail_msg, fail_len, 0x0C, 0xFFFF, 23
    .sigue:
    pop ax
    mov byte [gs:si], al
    pop ax
    mov byte [fs:di], al
    mov ax, 0
    je .exit
    mov ax, 1
    .exit:
    pop si
    pop di
    pop gs
    pop fs
    popf
    ret
