/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#include "gdt.h"

gdt_entry gdt[GDT_COUNT] = {
    /* Descriptor nulo*/
    /* Offset = 0x00 */
    [GDT_IDX_NULL_DESC] = (gdt_entry) {
        (uint16_t)    0x0000,         /* limit[0:15]  */
        (uint16_t)    0x0000,         /* base[0:15]   */
        (uint8_t)     0x00,           /* base[23:16]  */
        (uint8_t)     0x00,           /* type         */
        (uint8_t)     0x00,           /* s            */
        (uint8_t)     0x00,           /* dpl          */
        (uint8_t)     0x00,           /* p            */
        (uint8_t)     0x00,           /* limit[16:19] */
        (uint8_t)     0x00,           /* avl          */
        (uint8_t)     0x00,           /* l            */
        (uint8_t)     0x00,           /* db           */
        (uint8_t)     0x00,           /* g            */
        (uint8_t)     0x00,           /* base[31:24]  */
    },
    [10] = (gdt_entry) {
    .limit_0_15 = 0xc8ff,
    .base_0_15 = 0,
    .base_23_16 = 0,
    .type = 0b0010,
    .s = 1,
    .dpl = 0,
    .p = 1,
    .limit_16_19 = 0,
    .avl = 0,
    .l = 0,
    .db = 1,
    .g = 1,
    .base_31_24 = 0,
    },
    [11] = (gdt_entry) {
    .limit_0_15 = 0xc8ff,
    .base_0_15 = 0,
    .base_23_16 = 0,
    .type = 0b1010,
    .s = 1,
    .dpl = 0,
    .p = 1,
    .limit_16_19 = 0,
    .avl = 0,
    .l = 0,
    .db = 1,
    .g = 1,
    .base_31_24 = 0,
    },
    [12] = (gdt_entry) {
    .limit_0_15 = 0xc8ff,
    .base_0_15 = 0,
    .base_23_16 = 0,
    .type = 0b0010,
    .s = 1,
    .dpl = 3,
    .p = 1,
    .limit_16_19 = 0,
    .avl = 0,
    .l = 0,
    .db = 1,
    .g = 1,
    .base_31_24 = 0,
    },
    [13] = (gdt_entry) {
    .limit_0_15 = 0xc8ff,
    .base_0_15 = 0,
    .base_23_16 = 0,
    .type = 0b1010,
    .s = 1,
    .dpl = 3,
    .p = 1,
    .limit_16_19 = 0,
    .avl = 0,
    .l = 0,
    .db = 1,
    .g = 1,
    .base_31_24 = 0,
    },
    [14] = (gdt_entry) {
    .limit_0_15 = 0xffff,
    .base_0_15 = 0,
    .base_23_16 = 0x0A,
    .type = 0b0010,
    .s = 1,
    .dpl = 0,
    .p = 1,
    .limit_16_19 = 0x1,
    .avl = 0,
    .l = 0,
    .db = 1,
    .g = 0,
    .base_31_24 = 0,
    },
    [15] = (gdt_entry) {
    .limit_0_15 = 0x7fff,
    .base_0_15 = 0x8000,
    .base_23_16 = 0x0B,
    .type = 0b0010,
    .s = 1,
    .dpl = 0,
    .p = 1,
    .limit_16_19 = 0,
    .avl = 0,
    .l = 0,
    .db = 1,
    .g = 0,
    .base_31_24 = 0,
    }

    
};

gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,
    (uint32_t) &gdt
};
