%include "print.mac"

BITS 32

sched_task_offset:     dd 0xFFFF
sched_task_selector:   dw 0xFFFFFFFF

;; PIC
extern pic_finish1

;; Sched
extern sched_nextTask


%macro ISR 1
global _isr%1

_isr%1:
    mov eax, %1
    jmp $

%endmacro


;; Exceptions
;; -------------------------------------------------------------------------- ;;
ISR 0

;; Clock
;; -------------------------------------------------------------------------- ;;

;; Keyboard
;; -------------------------------------------------------------------------- ;;

;; Syscalls
;; -------------------------------------------------------------------------- ;;

;; Aux
;; -------------------------------------------------------------------------- ;;
isrNumber:           dd 0x00000000
isrClock:            db '|/-\'
nextClock:
        pushad
        inc DWORD [isrNumber]
        mov ebx, [isrNumber]
        cmp ebx, 0x4
        jl .ok
                mov DWORD [isrNumber], 0x0
                mov ebx, 0
        .ok:
                add ebx, isrClock
                print_text_pm ebx, 1, 0x0f, 49, 79
                popad
        ret
