#ifndef __IDT_H__
#define __IDT_H__

#include "stdint.h"

/* IDT descriptor */
typedef struct str_idt_descriptor {
    uint16_t idt_length;
    uint32_t idt_addr;
} __attribute__((__packed__)) idt_descriptor;

/* IDT emtry */
typedef struct str_idt_entry_fld {
    uint16_t offset_0_15;
    uint16_t segsel;
    uint16_t attr;
    uint16_t offset_16_31;
} __attribute__((__packed__, aligned (8))) idt_entry;

extern idt_entry idt[];
extern idt_descriptor IDT_DESC;

void idt_init();

#endif  /* !__IDT_H__ */
