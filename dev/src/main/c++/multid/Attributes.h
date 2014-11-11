#ifndef _Attributes_h
#define _Attributes_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Color.h>

class Prims;
class GeomObj;

class Attributes
{
public:
	Attributes(void);
	virtual ~Attributes(void);

	virtual void apply(const GeomObj &geom_obj, Prims &prims) const = 0;
};

inline
Attributes::Attributes(void)
{
}

inline
Attributes::~Attributes(void)
{
}

class NoAttributes
	: public Attributes
{
public:
	NoAttributes(void);
	~NoAttributes(void);

	void apply(const GeomObj &geom_obj, Prims &prims) const;
};

inline
NoAttributes::NoAttributes(void)
{
}

inline
NoAttributes::~NoAttributes(void)
{
}

class ColorAttributes
	: public Attributes
{
public:
	ColorAttributes(const Color &color_);
	~ColorAttributes(void);

	void apply(const GeomObj &geom_obj, Prims &prims) const;

	static const ColorAttributes *const BACKGROUND;
	static const ColorAttributes *const FOREGROUND;
	static const ColorAttributes *const RED;
	static const ColorAttributes *const GREEN;
	static const ColorAttributes *const BLUE;
	static const ColorAttributes *const CYAN;
	static const ColorAttributes *const MAGENTA;
	static const ColorAttributes *const YELLOW;

private:
	Color color;
};

inline
ColorAttributes::ColorAttributes(const Color &color_)
	: color(color_)
{
}

inline
ColorAttributes::~ColorAttributes(void)
{
}

#endif
