%include "print.mac"

global start
extern GDT_DESC
extern screen_drawPixel
extern screen_drawBox
extern screen_reset

jmp start

start_rm_msg db     'Starting kernel in real mode'
start_rm_len equ    $ - start_rm_msg

start_pm_msg db     'Starting protected mode'
start_pm_len equ    $ - start_pm_msg

DS_RING_0 equ 0x0a << 3
CS_RING_0 equ 0x0b << 3
DS_RING_3 equ 0x0c << 3
CS_RING_3 equ 0x0d << 3
VRAM equ 0x0f << 3

;;
;; Code section
;; -------------------------------------------------------------------------- ;;

BITS 16
start:
    cli

    mov ax, 0003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font

    print_text_rm start_rm_msg, start_rm_len, 0x07, 0, 0
    

    call A20_disable
    call A20_check
    call A20_enable
    call A20_check
    lgdt [GDT_DESC]

    mov eax, cr0
    xor eax, 0x01
    mov cr0, eax
    jmp CS_RING_0:protected_mode
BITS 32
protected_mode:
    mov eax, DS_RING_0
    mov es, eax
    mov ds, eax
    mov fs, eax
    mov ss, eax
    mov eax, 0x25000
    mov ebp, eax
    mov esp, eax
    print_text_pm start_pm_msg, start_pm_len, 0x07, 5, 0

    push 2
    push 0x43
    push 80
    push 40
    push 0
    push 0
    xchg bx, bx
    call screen_reset
    jmp $

    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
