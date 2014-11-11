#ifndef _Point_h
#define _Point_h
#ifdef __GNUC__
#pragma interface
#endif

#include <exception>
#include <Color.h>
#include <Space.h>
#include <Map.h>
#include <GeomObj.h>

class ActualPoint
	: public ActualGeomObj
{
protected:
	ActualPoint(const Space &space_);
	ActualPoint(const Space &space_, std::istream &is);
	ActualPoint(const ActualPoint &actual_point);
	ActualPoint(const Map &map, const ActualPoint &actual_point);
	~ActualPoint(void);

	ActualGeomObj *image(const Map &map) const;
	void draw(Prims &prims) const;
	void print(std::ostream &os) const;

	class IncompatibleMapDomain
		: public std::exception { };

private:
	ActualPoint &operator=(const ActualPoint &); // Do not define.

	Color color;
	double *coords; // single subscript for efficiency

	friend class Point;
};

inline
ActualPoint::ActualPoint(const Space &space_)
	: ActualGeomObj(space_),
	  color(Color::FOREGROUND),
	  coords(0)
{
	coords = new double[space().dim()];
}

inline
ActualPoint::ActualPoint(const Map &map, const ActualPoint &actual_point)
	: ActualGeomObj(map.codomain()),
	  color(actual_point.color),
	  coords(0)
{
#ifdef ERROR_CHECKING
	if (&map.domain() != &actual_point.space())
		throw IncompatibleMapDomain();
#endif
	coords = new double[space().dim()];
	map.apply(actual_point.coords, coords);
}

inline
ActualPoint::~ActualPoint(void)
{
	delete[] coords;
}

inline ActualGeomObj *
ActualPoint::image(const Map &map) const
{
	ActualPoint *mapped = new ActualPoint(map, *this);
	return mapped;
}

class Point
	: public GeomObj
{
public:
	Point(const Space &space);
	Point(const Space &space, std::istream &is);
	Point(const Point &point);
	Point(const Map &map, const Point &point);
	~Point(void);

	Color color(void) const;
	Color &color(void);

	double operator[](int index) const;
	double &operator[](int index);

	static const std::string name;

	class RangeViolation
		: public std::exception { };

protected:
	const ActualPoint *actual_point(void) const;
	ActualPoint *actual_point(void);
	void make_actual(void);
};

inline
Point::Point(const Space &space_)
	: GeomObj(new ActualPoint(space_))
{
}

inline
Point::Point(const Space &space_, std::istream &is)
	: GeomObj(new ActualPoint(space_, is))
{
}

inline
Point::Point(const Point &point)
	: GeomObj(point)
{
}

inline
Point::Point(const Map &map, const Point &point)
	: GeomObj(map, point)
{
}

inline const ActualPoint *
Point::actual_point(void) const
{
	return dynamic_cast<ActualPoint *>(actual);
}

inline ActualPoint *
Point::actual_point(void)
{
	return dynamic_cast<ActualPoint *>(actual);
}

inline Color
Point::color(void) const
{
	return actual_point()->color;
}

inline Color &
Point::color(void)
{
	make_actual();
	return actual_point()->color;
}

inline double &
Point::operator[](int index)
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= space().dim())
		throw RangeViolation();
#endif
	make_actual();
	return actual_point()->coords[index];
}

#endif
