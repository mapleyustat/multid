#ifndef _Color_h
#define _Color_h
#ifdef __GNUC__
#pragma interface
#endif

#include <iostream>

class Prims;
class PrimsPS;

class Color
/*
    Contains an RGB value. Can be constructed in a variety of ways.
*/
{
    friend class Prims;
    friend class PrimsPS;
// Colors are loaded there.

public:
    Color(void);
    Color(const Color &color, double intensity);
    Color(const double r,const double g,const double b);
        Color(const double *rgb);

    static Color BACKGROUND, FOREGROUND,
        RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW;

    static void init();
private:

    double R,G,B;

/*
    The following are irrelevant in RGB mode.

    Color(unsigned long index_);
    operator unsigned long() const;

    unsigned long index;

    friend class ColorArray; // init(int n_colors, const Color *colors)
*/
    friend std::ostream & operator<<(std::ostream &os, const Color &color);
};


std::ostream &
operator<<(std::ostream &os, const Color &color);

std::istream &
operator>>(std::istream &is, Color &color);

#endif
