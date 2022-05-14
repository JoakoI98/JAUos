#include "syscall.h" 

void task() {
    // breakpoint();
    while(1) {
        syscall_usePortalGun(4, 0, 1, 0);
    };
}
