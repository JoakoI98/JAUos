; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "print.mac"

global start
extern GDT_DESC
extern screen_drawPixel
extern screen_drawBox
extern screen_reset

;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
start_rm_msg db     'Iniciando kernel en Modo Real'
start_rm_len equ    $ - start_rm_msg

start_pm_msg db     'Iniciando kernel en Modo Protegido'
start_pm_len equ    $ - start_pm_msg

DS_RING_0 equ 0x0a << 3
CS_RING_0 equ 0x0b << 3
DS_RING_3 equ 0x0c << 3
CS_RING_3 equ 0x0d << 3
VRAM equ 0x0f << 3

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; Cambiar modo de video a 80 X 50
    mov ax, 0003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font

    ; Imprimir mensaje de bienvenida
    print_text_rm start_rm_msg, start_rm_len, 0x07, 0, 0
    

    ; Habilitar A20
    call A20_disable
    call A20_check
    call A20_enable
    call A20_check
    ; Cargar la GDT
    lgdt [GDT_DESC]

    ; Setear el bit PE del registro CR0
    mov eax, cr0
    xor eax, 0x01
    mov cr0, eax
    ; Saltar a modo protegido
    jmp CS_RING_0:protected_mode
BITS 32
protected_mode:
    ; Establecer selectores de segmentos
    mov eax, DS_RING_0
    mov es, eax
    mov ds, eax
    mov fs, eax
    mov ss, eax
    mov eax, 0x25000
    ; Establecer la base de la pila
    mov ebp, eax
    mov esp, eax
    ; Imprimir mensaje de bienvenida
    print_text_pm start_pm_msg, start_pm_len, 0x07, 5, 0
    ; Inicializar pantalla

    push 2
    push 0x43
    push 80
    push 40
    push 0
    push 0
    xchg bx, bx
    call screen_reset
    jmp $

    

    
    ; Inicializar el manejador de memoria
 
    ; Inicializar el directorio de paginas
    
    ; Cargar directorio de paginas

    ; Habilitar paginacion
    
    ; Inicializar tss

    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT
    
    ; Cargar IDT
 
    ; Configurar controlador de interrupciones

    ; Cargar tarea inicial

    ; Habilitar interrupciones

    ; Saltar a la primera tarea: Idle

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
