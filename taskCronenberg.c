#include "syscall.h" 

void task() {
    while(1) {
        __asm __volatile("nop" : : );
    };
}

