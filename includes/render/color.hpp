#ifndef COLORS_H
#define COLORS_H

#define COLOR_TRANSPARENT -1
#define COLOR_BLACK   0
#define COLOR_RED     1
#define COLOR_GREEN   2
#define COLOR_YELLOW  3
#define COLOR_BLUE    4
#define COLOR_MAGENTA 5
#define COLOR_CYAN    6
#define COLOR_WHITE   7

typedef short Color;

namespace Colors {
    enum ColorBunch {
        light_green=20,
        green,
        dark_green,
        white,
        grey,
        dark_grey,
        light_grey,
        black,
        light_red,
        red,
        yellow,
        night,
        sky_blue,
        orange_red,
        dark_red,
        pink,
        light_pink,
    };
}



#endif