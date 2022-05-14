#ifndef __SCREEN_H__
#define __SCREEN_H__

#define VIDEO_ROWS 50
#define VIDEO_COLUMNS 80

#include "stdint.h"
#include "colors.h"
#include "defines.h"

/* Video memory struct */
typedef struct ca_s {
    uint8_t c;
    uint8_t a;
} ca;

typedef struct str_info_loop {
    char *label;
    uint8_t offset;
} info_loop_s;


void print(const char* text, uint32_t y, uint32_t x, uint8_t fg, uint8_t bg);
void print_dec(uint32_t number, uint32_t size, uint32_t x, uint32_t y, uint8_t fg, uint8_t bg);
void print_hex(uint32_t number, int32_t size, uint32_t x, uint32_t y, uint8_t fg, uint8_t bg);

void screen_drawBox(uint32_t fInit, uint32_t cInit,
                    uint32_t fSize, uint32_t cSize,
                    uint8_t character, uint8_t color );

void screen_drawPixel(uint32_t row,
                    uint32_t column,
                    uint8_t character,
                    uint8_t fg,
                    uint8_t bg
                    );

void screen_reset();

#endif  /* !__SCREEN_H__ */
