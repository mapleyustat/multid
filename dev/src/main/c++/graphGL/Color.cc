#ifdef __GNUC__
#pragma implementation
#endif
#define GRAPHICS_IMPLEMENTATION
#include <iostream>
#include <ctype.h>
#include <Color.h>

enum ColorIndex { _BACKGROUND,_FOREGROUND,_RED,_GREEN,
	_BLUE,_CYAN,_MAGENTA,_YELLOW };
const int NumColors = 8;

const double RGB_source[NumColors*3]
	= { 0.0f, 0.0f, 0.0f,
	    1.0f, 1.0f, 1.0f,
	    1.0f, 0.0f, 0.0f,
	    0.0f, 1.0f, 0.0f,
	    0.0f, 0.2f, 1.0f,
	    0.0f, 0.5f, 1.0f,
	    0.8f, 0.1f, 0.1f,
	    1.0f, 1.0f, 0.0f };

Color Color::BACKGROUND(&RGB_source[3*_BACKGROUND]);
Color Color::FOREGROUND(&RGB_source[3*_FOREGROUND]);
Color Color::RED(&RGB_source[3*_RED]);
Color Color::GREEN(&RGB_source[3*_GREEN]);
Color Color::BLUE(&RGB_source[3*_BLUE]);
Color Color::CYAN(&RGB_source[3*_CYAN]);
Color Color::MAGENTA(&RGB_source[3*_MAGENTA]);
Color Color::YELLOW(&RGB_source[3*_YELLOW]);

void Color::init() {
	static int beenhere;
	if (beenhere) return;
	beenhere = 1;
	BACKGROUND = Color(&RGB_source[3*_BACKGROUND]);
	FOREGROUND = Color(&RGB_source[3*_FOREGROUND]);
	RED = Color(&RGB_source[3*_RED]);
	GREEN = Color(&RGB_source[3*_GREEN]);
	BLUE = Color(&RGB_source[3*_BLUE]);
	CYAN = Color(&RGB_source[3*_CYAN]);
	MAGENTA = Color(&RGB_source[3*_MAGENTA]);
	YELLOW = Color(&RGB_source[3*_YELLOW]);
}

Color::Color(void)
    : R(RGB_source[3]),
      G(RGB_source[4]),
      B(RGB_source[5])
{
}

Color::Color(const Color &color, double intensity)
    : R(RGB_source[3]),
      G(RGB_source[4]),
      B(RGB_source[5])
{
    if (intensity<0.) intensity=0.;
    if (intensity>1.) intensity=1.;
    R=color.R*intensity;
    G=color.G*intensity;
    B=color.B*intensity;
}

Color::Color(const double r,const double g,const double b)
    : R(r),
      G(g),
      B(b)
{
}

Color::Color(const double* rgb)
    : R(rgb[0]),
      G(rgb[1]),
      B(rgb[2])
{
}

std::ostream &
operator<<(std::ostream &os, const Color &color)
{
/*
    This can wait: outputting the "nearest pure" color name is not so simple
    in true color environment.
*/

/*
    unsigned long index = color.index;
    unsigned long nearest_pure; // BG = 0, FG = 1, R = 2, etc.
    if (index == 0)
        nearest_pure = 0;
    else
        nearest_pure = 1 + (index - 1)/SEG_LENGTH;
    static const std::string names[]
        = { "BG", "FG", "R", "G", "B", "C", "M", "Y" };
    os << names[nearest_pure];
    nearest_pure *= SEG_LENGTH;
    if (index != nearest_pure)
        os << (1. - (nearest_pure - index)/double(SEG_LENGTH - 1));
*/
    os << "c " << color.R << " " << color.G << " " << color.B;
    return os;
}

std::istream &
operator>>(std::istream &is, Color &color)
{
    char c;
    is >> c;
    if (c == 'c') {
        double rgb[3];
        is >> rgb[0] >> rgb[1] >> rgb[2];
        if (is)
            color = Color(rgb);
        else
            color = Color::FOREGROUND;
        return is;
    }
    if (c == 'F')
        is.ignore();
    else if (c == 'B') {
        if (is.peek() == 'G') {
            is.ignore();
            color = Color::BACKGROUND;
            return is;
        }
    }
    switch (c) {
    case 'R':   color = Color::RED;         break;
    case 'G':   color = Color::GREEN;       break;
    case 'B':   color = Color::BLUE;        break;
    case 'C':   color = Color::CYAN;        break;
    case 'M':   color = Color::MAGENTA;     break;
    case 'Y':   color = Color::YELLOW;      break;
    default:
    case 'F':   color = Color::FOREGROUND;  break;
    }
    if (is.eof() || is.fail()) return is;
    if (!isspace(is.peek())) {
        double intensity;
        is >> intensity;
        Color subdued(color, intensity);
        color = subdued;
    }
    return is;
}
