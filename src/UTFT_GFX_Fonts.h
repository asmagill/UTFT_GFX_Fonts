#ifndef _UTFT_GFX_Fonts_H
#define _UTFT_GFX_Fonts_H

#include <Adafruit_GFX.h>

struct _current_font {
    uint8_t* font ;
    uint8_t  x_size ;
    uint8_t  y_size ;
    uint8_t  offset ;
    uint8_t  numchars ;
} ;

// VGA color palette
#define VGA_BLACK       0x0000
#define VGA_WHITE       0xFFFF
#define VGA_RED         0xF800
#define VGA_GREEN       0x0400
#define VGA_BLUE        0x001F
#define VGA_SILVER      0xC618
#define VGA_GRAY        0x8410
#define VGA_MAROON      0x8000
#define VGA_YELLOW      0xFFE0
#define VGA_OLIVE       0x8400
#define VGA_LIME        0x07E0
#define VGA_AQUA        0x07FF
#define VGA_TEAL        0x0410
#define VGA_NAVY        0x0010
#define VGA_FUCHSIA     0xF81F
#define VGA_PURPLE      0x8010
#define VGA_TRANSPARENT 0xFFFFFFFF

// These are labels which can be used as x values to the print methods to cause calculations based on TFT
// size and orientation.  RIGHT and CENTER should be values that are normally well off screen to minimize
// the chance that they could have been passed in accidentally
#define UTFT_LEFT   0
#define UTFT_RIGHT  9999
#define UTFT_CENTER 9998
// Not in the core UTFT library, but seemed like a good idea for vertical placement as well
#define UTFT_TOP    0
#define UTFT_BOTTOM 9997
#define UTFT_MIDDLE 9998

class UTFT_GFX_Fonts {
    public:
        UTFT_GFX_Fonts(Adafruit_GFX* gfx) ;

        void     print(char* st,  int16_t x, int16_t y, int16_t deg = 0) ;
        void     print(String st, int16_t x, int16_t y, int16_t deg = 0) ;
        void     printNumI(int32_t num, int16_t x, int16_t y, int8_t length = 0, char filler = ' ') ;
        void     printNumF(double num, uint8_t dec, int16_t x, int16_t y, char divider = '.', int8_t length = 0, char filler = ' ') ;
        void     setFont(uint8_t* font) ;
        uint8_t* getFont() ;
        uint8_t  getFontXsize() ;
        uint8_t  getFontYsize() ;

        // Since we're replicating UTFT's approach, add these
        void     setColor(uint8_t r, uint8_t g, uint8_t b) ;
        void     setColor(uint16_t color) ;
        void     setBackColor(uint8_t r, uint8_t g, uint8_t b) ;
        void     setBackColor(uint32_t color) ;

        // But I like these better personally
        void     setTextColor(uint16_t c) ;
        void     setTextColor(uint16_t c, uint16_t bg) ;

    protected:
        void     printChar(uint8_t c, int16_t x, int16_t y) ;
        void     rotateChar(uint8_t c, int16_t x, int16_t y, int16_t pos, int16_t deg) ;

        _current_font cfont ;
        Adafruit_GFX* _gfx ;
        uint16_t      textcolor, textbgcolor ;
} ;

#endif
