#ifndef _Arrow_h
#define _Arrow_h
#ifdef __GNUC__
#pragma interface
#endif

#include <exception>
#include <Color.h>
#include <Space.h>
#include <Map.h>
#include <GeomObj.h>
#include <Point.h>

class ActualArrow
	: public ActualGeomObj
{
protected:
	explicit ActualArrow(const Point &origin_);
	ActualArrow(const Space &space_, std::istream &is);
	ActualArrow(const ActualArrow &actual_arrow);
	ActualArrow(const Map &map, const ActualArrow &actual_arrow);
	~ActualArrow(void);

	ActualGeomObj *image(const Map &map) const;
	void draw(Prims &prims) const;
	void print(std::ostream &os) const;

	class IncompatibleMapDomain
		: public std::exception { };
	class InappropriateDimension
		: public std::exception { };

private:
	ActualArrow &operator=(const ActualArrow &); // Do not define.

	Point origin;
	Color color;
	double *coords; // single subscript for efficiency

	friend class Arrow;
};

inline
ActualArrow::ActualArrow(const Point &origin_)
	: ActualGeomObj(origin_.space()),
	  origin(origin_),
	  color(Color::FOREGROUND),
	  coords(0)
{
	coords = new double[space().dim()];
}

inline
ActualArrow::ActualArrow(const ActualArrow &actual_arrow)
	: ActualGeomObj(actual_arrow.space()),
	  origin(actual_arrow.origin),
	  color(actual_arrow.color),
	  coords(0)
{
	int size = space().dim();
	coords = new double[size];
	for (int i = 0; i < size; ++i)
		coords[i] = actual_arrow.coords[i];
}

inline
ActualArrow::ActualArrow(const Map &map, const ActualArrow &actual_arrow)
	: ActualGeomObj(map.codomain()),
	  origin(map, actual_arrow.origin),
	  color(actual_arrow.color),
	  coords(0)
{
#ifdef ERROR_CHECKING
	if (&map.domain() != &actual_arrow.space())
		throw IncompatibleMapDomain();
#endif
	coords = new double[space().dim()];
	map.apply_derivative(actual_arrow.origin, actual_arrow.coords, coords);
}

inline
ActualArrow::~ActualArrow(void)
{
	delete[] coords;
}

inline ActualGeomObj *
ActualArrow::image(const Map &map) const
{
	ActualArrow *mapped = new ActualArrow(map, *this);
	return mapped;
}

class Arrow
	: public GeomObj
{
public:
	explicit Arrow(const Point &origin);
	Arrow(const Space &space_, std::istream &is);
	Arrow(const Arrow &arrow);
	Arrow(const Map &map, const Arrow &arrow);
	~Arrow(void);

	Point origin(void) const;

	Color color(void) const;
	Color &color(void);

	double operator[](int index) const;
	double &operator[](int index);

	static const std::string name;

	class RangeViolation
		: public std::exception { };

protected:
	const ActualArrow *actual_arrow(void) const;
	ActualArrow *actual_arrow(void);
	void make_actual(void);
};

inline
Arrow::Arrow(const Point &origin_)
	: GeomObj(new ActualArrow(origin_))
{
}

inline
Arrow::Arrow(const Arrow &arrow)
	: GeomObj(arrow)
{
}

inline
Arrow::Arrow(const Map &map, const Arrow &arrow)
	: GeomObj(map, arrow)
{
}

inline const ActualArrow *
Arrow::actual_arrow(void) const
{
	return dynamic_cast<ActualArrow *>(actual);
}

inline ActualArrow *
Arrow::actual_arrow(void)
{
	return dynamic_cast<ActualArrow *>(actual);
}

inline Point
Arrow::origin(void) const
{
	return actual_arrow()->origin;
}

inline Color
Arrow::color(void) const
{
	return actual_arrow()->color;
}

inline Color &
Arrow::color(void)
{
	make_actual();
	return actual_arrow()->color;
}

inline double
Arrow::operator[](int index) const
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= space().dim())
		throw RangeViolation();
#endif
	return actual_arrow()->coords[index];
}

inline double &
Arrow::operator[](int index)
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= space().dim())
		throw RangeViolation();
#endif
	make_actual();
	return actual_arrow()->coords[index];
}

#endif
