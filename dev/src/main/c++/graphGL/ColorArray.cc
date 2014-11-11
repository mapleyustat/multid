#ifdef __GNUC__
#pragma implementation
#endif
#define GRAPHICS_IMPLEMENTATION
#include <Color.h>
#include <ColorArray.h>

ColorArray::ColorArray(int n_colors_)
	: data(new Color[n_colors_]),
	  size(n_colors_)
{
}

ColorArray::~ColorArray(void)
{
	delete[] data;
}

int
ColorArray::n_colors(void) const
{
	return size;
}

const Color&
ColorArray::operator[](int index) const
{
	if (0 <= index && index < size)
		return data[index];
	else
		return Color::FOREGROUND;
}

void
ColorArray::set(int index, const Color &color)
{
	if (0 <= index && index < size)
		data[index] = color;
}
