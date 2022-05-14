#ifndef __PIC_H__
#define __PIC_H__

#include "stdint.h"

void pic_reset(void);
void pic_enable();
void pic_disable();

static __inline __attribute__((always_inline)) void outb(uint32_t port, uint8_t data);

void pic_finish1(void);
void pic_finish2(void);

#endif	/* !__PIC_H__ */
