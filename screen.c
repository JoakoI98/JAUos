#include "screen.h"
#include "colors.h"
#include "i386.h"

void print(const char* text, uint32_t y, uint32_t x, uint8_t fg, uint8_t bg) {
    int32_t i;
    for (i = 0; text[i] != 0; i++) {
        screen_drawPixel(y,x,text[i],fg,bg);
        x++;
        if (x == VIDEO_COLUMNS) {
            x = 0;
        }
    }
}

void print_dec(uint32_t number, uint32_t size, uint32_t y, uint32_t x, uint8_t fg, uint8_t bg) {
    uint32_t i;
    uint8_t letters[16] = "0123456789";

    for(i = 0; i < size; i++) {
        uint32_t remainder  = number % 10;
        number = number / 10;
        screen_drawPixel(y,x + size - i - 1,letters[remainder],fg,bg);
    }
}

void print_hex(uint32_t number, int32_t size, uint32_t y, uint32_t x, uint8_t fg, uint8_t bg) {
    int32_t i;
    uint8_t hexa[8];
    uint8_t letters[16] = "0123456789ABCDEF";
    hexa[0] = letters[ ( number & 0x0000000F ) >> 0  ];
    hexa[1] = letters[ ( number & 0x000000F0 ) >> 4  ];
    hexa[2] = letters[ ( number & 0x00000F00 ) >> 8  ];
    hexa[3] = letters[ ( number & 0x0000F000 ) >> 12 ];
    hexa[4] = letters[ ( number & 0x000F0000 ) >> 16 ];
    hexa[5] = letters[ ( number & 0x00F00000 ) >> 20 ];
    hexa[6] = letters[ ( number & 0x0F000000 ) >> 24 ];
    hexa[7] = letters[ ( number & 0xF0000000 ) >> 28 ];
    for(i = 0; i < size; i++) {
        screen_drawPixel(y, x + size - i - 1,hexa[i],fg,bg);
    }
}

void screen_drawBox(uint32_t fInit,
                    uint32_t cInit,
                    uint32_t fSize,
                    uint32_t cSize,
                    uint8_t character,
                    uint8_t color ) {
    uint8_t effectiveColor = color & 0b111;
    uint8_t attr = 0x80 | effectiveColor | (effectiveColor << 4);
    ca (*p)[VIDEO_COLUMNS] = (ca (*)[VIDEO_COLUMNS]) VIDEO;
    uint32_t f;
    uint32_t c;
    for (f = fInit; f < fInit+fSize; f++) {
    for (c = cInit; c < cInit+cSize; c++) {
          p[f][c].c = character;
          p[f][c].a = attr;
    }}
}

void screen_drawPixel(uint32_t row,
                    uint32_t column,
                    uint8_t character,
                    uint8_t fg,
                    uint8_t bg
                    ) {
    fg = fg & 0b1111;
    bg = bg & 0b111;
    uint8_t attr = 0x00 | fg | (bg << 4);
    ca (*p)[VIDEO_COLUMNS] = (ca (*)[VIDEO_COLUMNS]) VIDEO;
    p[row][column].c = character;
    p[row][column].a = attr;
}

#define PLAYABLE_BKG C_FG_GREEN

#define PLAYABLE_ZONE 0, 0, 40, 80
#define NON_PLAYABLE_ZONE 39, 0, 10, 80

#define P0_BG C_FG_RED
#define P0_FG C_FG_WHITE

#define P1_BG C_FG_BLUE
#define P1_FG C_FG_WHITE

#define P0_START_Y 44 
#define P0_START_X 5 

#define P1_START_Y  44
#define P1_START_X  64


#define POINTS_ZONE_SIZE 10
#define POINTS_ZONE_SIZE_Y 3

#define TASK_NUM_SIZE 2
#define TASK_NUM_START_X 24

void screen_drawPoints(uint32_t p0, uint32_t p1) {
    screen_drawBox(P0_START_Y - 1,P0_START_X - 1,POINTS_ZONE_SIZE_Y,POINTS_ZONE_SIZE + 2,0,P0_BG);
    screen_drawBox(P1_START_Y - 1,P1_START_X - 1,POINTS_ZONE_SIZE_Y,POINTS_ZONE_SIZE + 2,0,P1_BG);
    print_dec(p0,POINTS_ZONE_SIZE,P0_START_Y,P0_START_X,P0_FG,P0_BG);
    print_dec(p1,POINTS_ZONE_SIZE,P1_START_Y,P1_START_X,P1_FG,P1_BG);
}

void screen_drawTasks(){
    uint8_t i;
    for(i = 0; i != 10; i++){
        print_dec(i,TASK_NUM_SIZE,P0_START_Y - 2,TASK_NUM_START_X + 3*i, P0_BG, 0);
        screen_drawPixel(P0_START_Y - 1, TASK_NUM_START_X + 3*i, '-', P0_FG, 0);
        
        print_dec(i,TASK_NUM_SIZE,P1_START_Y + 1,TASK_NUM_START_X + 3*i, P1_BG, 0);
        screen_drawPixel(P1_START_Y + 2, TASK_NUM_START_X + 3*i, ':', P0_FG, 0);
    }
}



#define INFO_ZONE_SIZE 40
#define INFO_ZONE_START_X 19
#define INFO_ZONE_START_Y 0

#define INFO_ZONE INFO_ZONE_START_Y, INFO_ZONE_START_X, 40, INFO_ZONE_SIZE
#define INFO_BKG C_FG_BLACK

#define INFO_INFO_TEXT_BG C_FG_BLACK
#define INFO_INFO_TEXT_FG C_FG_GREEN

#define INFO_REGS_TEXT_BG C_FG_BLACK
#define INFO_REGS_TEXT_FG C_FG_WHITE

#define INFO_LOOP_SIZE 16
info_loop_s info_loop[INFO_LOOP_SIZE] = {
    {.label="eax:", .offset = 0},
    {.label="ebx:", .offset = 1},
    {.label="ecx:", .offset = 2},
    {.label="edx:", .offset = 3},
    {.label="esi:", .offset = 4},
    {.label="edi:", .offset = 5},
    {.label="ebp:", .offset = 6},
    {.label="esp:", .offset = 7},
    {.label="eip:", .offset = 8},
    {.label="cs:", .offset = 9},
    {.label="ds:", .offset = 10},
    {.label="es:", .offset = 11},
    {.label="fs:", .offset = 12},
    {.label="gs:", .offset = 13},
    {.label="ss:", .offset = 14},
    {.label="fgl:", .offset = 15},
};


void screen_drawInfo( char *infoText, uint32_t *data){
    screen_drawBox(INFO_ZONE,0,INFO_BKG);
    uint8_t i = 0;
    uint8_t y = 0;
    while(infoText[i] != 0){
        uint8_t xOffset = INFO_ZONE_START_X + 1 + (i % (INFO_ZONE_SIZE - 2));
        if(i % (INFO_ZONE_SIZE - 2) == 0) y++;
        if(y > 4) break;
        screen_drawPixel(INFO_ZONE_START_Y + y, xOffset, infoText[i], INFO_INFO_TEXT_FG, INFO_INFO_TEXT_BG);
        i++;
    }

    
    for(uint8_t i = 0; i != INFO_LOOP_SIZE; i++){
        print(info_loop[i].label,INFO_ZONE_START_Y + 5 + 2*i, INFO_ZONE_START_X + 2, INFO_REGS_TEXT_FG, INFO_REGS_TEXT_BG);
        print_hex(data[info_loop[i].offset], 8,INFO_ZONE_START_Y + 5 + 2*i, INFO_ZONE_START_X + 2 + 5, INFO_REGS_TEXT_FG, INFO_REGS_TEXT_BG);
    }

    uint32_t cr0 = rcr0();
    uint32_t cr2 = rcr2();
    uint32_t cr3 = rcr3();
    uint32_t cr4 = rcr4();

    print("cr0:",INFO_ZONE_START_Y + 5 + 2*0, INFO_ZONE_START_X + INFO_ZONE_SIZE - 15, INFO_REGS_TEXT_FG, INFO_REGS_TEXT_BG);
    print_hex(cr0, 8,INFO_ZONE_START_Y + 5 + 2*0, INFO_ZONE_START_X + INFO_ZONE_SIZE - 15 + 5, INFO_REGS_TEXT_FG, INFO_REGS_TEXT_BG);


    print("cr2:",INFO_ZONE_START_Y + 5 + 2*1, INFO_ZONE_START_X + INFO_ZONE_SIZE - 15, INFO_REGS_TEXT_FG, INFO_REGS_TEXT_BG);
    print_hex(cr2, 8,INFO_ZONE_START_Y + 5 + 2*1, INFO_ZONE_START_X + INFO_ZONE_SIZE - 15 + 5, INFO_REGS_TEXT_FG, INFO_REGS_TEXT_BG);

    print("cr3:",INFO_ZONE_START_Y + 5 + 2*2, INFO_ZONE_START_X + INFO_ZONE_SIZE - 15, INFO_REGS_TEXT_FG, INFO_REGS_TEXT_BG);
    print_hex(cr3, 8,INFO_ZONE_START_Y + 5 + 2*2, INFO_ZONE_START_X + INFO_ZONE_SIZE - 15 + 5, INFO_REGS_TEXT_FG, INFO_REGS_TEXT_BG);

    print("cr4:",INFO_ZONE_START_Y + 5 + 2*3, INFO_ZONE_START_X + INFO_ZONE_SIZE - 15, INFO_REGS_TEXT_FG, INFO_REGS_TEXT_BG);
    print_hex(cr4, 8,INFO_ZONE_START_Y + 5 + 2*3, INFO_ZONE_START_X + INFO_ZONE_SIZE - 15 + 5, INFO_REGS_TEXT_FG, INFO_REGS_TEXT_BG);

}



void screen_reset() {
    screen_drawBox(PLAYABLE_ZONE,0,PLAYABLE_BKG);
    screen_drawBox(NON_PLAYABLE_ZONE,0,0);
    screen_drawPoints(0,0);

    screen_drawPixel(P0_START_Y - 1, P0_START_X + POINTS_ZONE_SIZE + 3, 'R', P0_BG, 0);
    screen_drawPixel(P0_START_Y + 1, P0_START_X + POINTS_ZONE_SIZE + 3, '-', P0_FG, 0);

    screen_drawPixel(P1_START_Y - 1, P1_START_X - 4, 'M', P1_BG, 0);
    screen_drawPixel(P1_START_Y + 1, P1_START_X - 4, ':', P1_FG, 0);
    screen_drawTasks();
    uint32_t testData[INFO_LOOP_SIZE] = {
        0x1234abcd,
        0x00abcd,
        0x12bcd,
        0x34abcd,
        0x1234bcd,
        0x1234cd,
        0x1abcd,
        0x123bcd,
        0x12abcd,
        0x12cd,
        0x12d,
        0x1234abcd,
        0x1b,
        0x12,
        0xbcd,
        0xbcd123,
    };
    screen_drawInfo("Page fault", testData);
    //uint32_t test = rcr0();
    //print_hex(test, 8 ,0 ,0,0);
}


