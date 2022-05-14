/*
Global defines
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Bool */
/* -------------------------------------------------------------------------- */
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1

/* Atributos paginas */
/* -------------------------------------------------------------------------- */
#define PAG_P                   0x00000001
#define PAG_R                   0x00000000
#define PAG_RW                  0x00000002
#define PAG_S                   0x00000000
#define PAG_US                  0x00000004

/* Misc */
/* -------------------------------------------------------------------------- */
#define SIZE_N                  40 // X
#define SIZE_M                  80 // Y

/* GDT indeces */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 35

#define GDT_IDX_NULL_DESC           0

/*GDT offset */
/* -------------------------------------------------------------------------- */
#define GDT_OFF_NULL_DESC           (GDT_IDX_NULL_DESC << 3)


/* Memory addresses */
/* -------------------------------------------------------------------------- */
#define BOOTSECTOR               0x00001000 /* direccion fisica de comienzo del bootsector (copiado) */
#define KERNEL                   0x00001200 /* direccion fisica de comienzo del kernel */
#define VIDEO                    0x000B8000 /* direccion fisica del buffer de video */

#define TASK_CODE             0x08000000 /* direccion virtual del codigo */

#define KERNEL_PAGE_DIR          0x00027000
#define KERNEL_PAGE_TABLE_0      0x00028000
#define CRYSTALS_MAP             0x00029000

#endif  /* !__DEFINES_H__ */
