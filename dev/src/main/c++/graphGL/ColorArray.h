#ifndef _ColorArray_h
#define _ColorArray_h
#ifdef __GNUC__
#pragma interface
#endif

class Color;

class ColorArray
/*
    Implements an array of Color objects.
*/
{
public:
    ColorArray(int n_colors);
    ~ColorArray(void);

    int n_colors(void) const;

    const Color& operator[](int index) const;
    void set(int index, const Color &color);

private:

    Color *data;
    int size;

    ColorArray(const ColorArray &color_array);      // Do not define.
    ColorArray &operator=(const ColorArray &color_array);   // Do not define.

};

#endif
