#include "UTFT_GFX_Fonts.h"

UTFT_GFX_Fonts::UTFT_GFX_Fonts(Adafruit_GFX* gfx) {
    _gfx           = gfx ;
    cfont.font     = NULL ;
    cfont.x_size   = 0 ;
    cfont.y_size   = 0 ;
    cfont.offset   = 0 ;
    cfont.numchars = 0 ;
    textcolor      = 0xFFFF ;
    textbgcolor    = 0xFFFF ;
}

void UTFT_GFX_Fonts::setTextColor(uint16_t c) {
    // For 'transparent' background, we'll set the bg
    // to the same as fg instead of using a flag
    textcolor = textbgcolor = c;
}

void UTFT_GFX_Fonts::setTextColor(uint16_t c, uint16_t b) {
    textcolor   = c;
    textbgcolor = b;
}

void UTFT_GFX_Fonts::setColor(uint8_t r, uint8_t g, uint8_t b) {
    textcolor = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3) ;
}

void UTFT_GFX_Fonts::setColor(uint16_t color) { textcolor = color ; }

void UTFT_GFX_Fonts::setBackColor(uint8_t r, uint8_t g, uint8_t b) {
    textbgcolor = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3) ;
}

void UTFT_GFX_Fonts::setBackColor(uint32_t color) {
    textbgcolor = (color == VGA_TRANSPARENT) ? textcolor : color ;
}


void UTFT_GFX_Fonts::print(char* st, int16_t x, int16_t y, int16_t deg) {
    int16_t stl = strlen(st) ;

    // UTFT_LEFT is already 0
    if (x == UTFT_RIGHT)  x = _gfx->width() - (stl * cfont.x_size) ;
    if (x == UTFT_CENTER) x = (_gfx->width() - (stl * cfont.x_size)) / 2 ;

    // UTFT_TOP is already 0
    if (y == UTFT_BOTTOM) y = _gfx->height() - cfont.y_size ;
    if (y == UTFT_MIDDLE) y = (_gfx->height() - cfont.y_size) / 2 ;

    for (int16_t i = 0 ; i < stl ; i++) {
        if (deg == 0) {
            printChar(*st++, x + (i * cfont.x_size), y) ;
        } else {
            rotateChar(*st++, x, y, i, deg) ;
        }
    }
}

void UTFT_GFX_Fonts::setFont(uint8_t* font) {
    cfont.font     = font ;
    cfont.x_size   = pgm_read_byte(&cfont.font[0]) ;
    cfont.y_size   = pgm_read_byte(&cfont.font[1]) ;
    cfont.offset   = pgm_read_byte(&cfont.font[2]) ;
    cfont.numchars = pgm_read_byte(&cfont.font[3]) ;
}

uint8_t* UTFT_GFX_Fonts::getFont()      { return cfont.font ; }
uint8_t  UTFT_GFX_Fonts::getFontXsize() { return cfont.x_size ; }
uint8_t  UTFT_GFX_Fonts::getFontYsize() { return cfont.y_size ; }


void UTFT_GFX_Fonts::print(String st, int16_t x, int16_t y, int16_t deg) {
    char buf[st.length() + 1] ;
    st.toCharArray(buf, st.length() + 1)  ;
    print(buf, x, y, deg) ;
}

void UTFT_GFX_Fonts::printNumI(int32_t num, int16_t x, int16_t y, int8_t length, char filler) {
    char buf[25] ;
    char st[27] ;
    boolean neg = false ;
    int8_t c = 0, f = 0 ;

    if (num == 0) {
        if (length != 0) {
            for (c = 0 ; c < (length - 1) ; c++) st[c] = filler ;
            st[c] = 48 ;
            st[c + 1] = 0 ;
        } else {
            st[0] = 48 ;
            st[1] = 0 ;
        }
    } else {
        if (num < 0) {
            neg = true ;
            num = -num ;
        }

        while (num > 0) {
            buf[c] = 48 + (num % 10) ;
            c++ ;
            num = (num - (num % 10)) / 10 ;
        }
        buf[c] = 0 ;

        if (neg) st[0] = 45 ;

        if (length > (c + neg)) {
            for (int8_t i = 0 ; i < (length - c - neg) ; i++) {
                st[i + neg] = filler ;
                f++ ;
            }
        }

        for (int8_t i = 0 ; i < c ; i++) st[i + neg + f] = buf[c - i - 1] ;
        st[c + neg + f] = 0 ;
    }

    print(st, x, y) ;
}

void UTFT_GFX_Fonts::printNumF(double num, uint8_t dec, int16_t x, int16_t y, char divider, int8_t length, char filler) {
    char st[27] ;
    boolean neg = false ;

    dec = constrain(dec, 1, 5) ;

    if (num < 0) neg = true ;

    dtostrf(num, length, dec, st) ;

    if (divider != '.') {
        for (uint8_t i = 0 ; i < sizeof(st) ; i++) if (st[i] == '.') st[i] = divider ;
    }

    if (filler != ' ') {
        if (neg) {
            st[0] = '-' ;
            for (uint8_t i = 1 ; i < sizeof(st) ; i++) if ((st[i] == ' ') || (st[i] == '-')) st[i] = filler ;
        } else {
            for (uint8_t i = 0 ; i < sizeof(st) ; i++) if (st[i] == ' ') st[i] = filler ;
        }
    }

    print(st, x, y) ;
}

void UTFT_GFX_Fonts::printChar(uint8_t c, int16_t x, int16_t y) {
    if (cfont.font == NULL) return ;

    uint16_t start = ((c - cfont.offset) * ((cfont.x_size / 8) * cfont.y_size)) + 4 ;
    bool     drawBG = (textbgcolor != textcolor) ;
    uint8_t  j, zz, ch, i ;

    for (j = 0 ; j < cfont.y_size ; j++) {
        for (zz = 0 ; zz < (cfont.x_size / 8) ; zz++) {
            ch = pgm_read_byte(&cfont.font[start + zz]) ;
            for (i = 0 ; i < 8 ; i++) {
                if ((ch & (1 << (7 - i))) != 0) {
                    _gfx->drawPixel(x + i + (zz * 8), y + j, textcolor) ;
                } else if (drawBG) {
                    _gfx->drawPixel(x + i + (zz * 8), y + j, textbgcolor) ;
                }
            }
        }
        start += (cfont.x_size / 8) ;
    }
}

void UTFT_GFX_Fonts::rotateChar(uint8_t c, int16_t x, int16_t y, int16_t pos, int16_t deg) {
    if (cfont.font == NULL) return ;

    uint16_t start = ((c - cfont.offset) * ((cfont.x_size / 8) * cfont.y_size)) + 4 ;
    double   radian = deg * 0.0175 ;
    bool     drawBG = (textbgcolor != textcolor) ;
    uint8_t  j, zz, ch, i ;
    int16_t  newx, newy ;

    for (j = 0 ; j < cfont.y_size ; j++) {
        for (zz = 0 ; zz < (cfont.x_size / 8) ; zz++) {
            ch = pgm_read_byte(&cfont.font[start + zz]) ;
            for (i = 0 ; i < 8 ; i++) {
                newx = x + (((i + (zz * 8) + (pos * cfont.x_size)) * cos(radian)) - (j * sin(radian))) ;
                newy = y + ((j * cos(radian)) + ((i + (zz * 8) + (pos * cfont.x_size)) * sin(radian))) ;
                if ((ch & (1 << (7 - i))) != 0) {
                    _gfx->drawPixel(newx, newy, textcolor) ;
                } else if (drawBG) {
                    _gfx->drawPixel(newx, newy, textbgcolor) ;
                }
            }
        }
        start += (cfont.x_size / 8) ;
    }
}
