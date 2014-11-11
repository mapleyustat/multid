#ifdef __GNUC__
#pragma implementation
#endif
#include <Prims.h>
#include "Attributes.h"

ColorAttributes *
init_attributes(const Color &c)
{
	Color::init();
	return new ColorAttributes(c);
}

const ColorAttributes *const ColorAttributes::BACKGROUND
        = init_attributes(Color::BACKGROUND);
const ColorAttributes *const ColorAttributes::FOREGROUND
        = init_attributes(Color::FOREGROUND);
const ColorAttributes *const ColorAttributes::RED
        = init_attributes(Color::RED);
const ColorAttributes *const ColorAttributes::GREEN
        = init_attributes(Color::GREEN);
const ColorAttributes *const ColorAttributes::BLUE
        = init_attributes(Color::BLUE);
const ColorAttributes *const ColorAttributes::CYAN
        = init_attributes(Color::CYAN);
const ColorAttributes *const ColorAttributes::MAGENTA
        = init_attributes(Color::MAGENTA);
const ColorAttributes *const ColorAttributes::YELLOW
        = init_attributes(Color::YELLOW);

void
NoAttributes::apply(const GeomObj & /* geom_obj */, Prims &prims) const
{
	prims.line_color(Color::FOREGROUND);
	prims.marker_color(Color::FOREGROUND);
	prims.edge_color(Color::FOREGROUND);
	prims.line_style(Prims::SOLID);
}

void
ColorAttributes::apply(const GeomObj & /* geom_obj */, Prims &prims) const
{
	prims.line_color(color);
	prims.marker_color(color);
	prims.edge_color(color);
	prims.line_style(Prims::SOLID);
}
