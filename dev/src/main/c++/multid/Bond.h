#ifndef _Bond_h
#define _Bond_h
#ifdef __GNUC__
#pragma interface
#endif

#include <exception>
#include <Color.h>
#include <Point.h>

class ActualBond
	: public ActualGeomObj
{
protected:
	explicit ActualBond(const Space &space_);
	ActualBond(const Space &space_, std::istream &is);
	ActualBond(const ActualBond &actual_bond);
	ActualBond(const Map &map, const ActualBond &actual_bond);
	~ActualBond(void);

	ActualGeomObj *image(const Map &map) const;
	void draw(Prims &prims) const;
	void print(std::ostream &os) const;

	class IncompatibleMapDomain
		: public std::exception { };

private:
	ActualBond &operator=(const ActualBond &); // Do not define.

	Color color;
	double *coords; // single subscript for efficiency

	friend class Bond;
};

inline
ActualBond::ActualBond(const Space &space_)
	: ActualGeomObj(space_),
	  color(Color::FOREGROUND),
	  coords(0)
{
	coords = new double[2*space().dim()];
}

inline
ActualBond::ActualBond(const Map &map, const ActualBond &actual_bond)
	: ActualGeomObj(map.codomain()),
	  color(actual_bond.color),
	  coords(0)
{
#ifdef ERROR_CHECKING
	if (&map.domain() != &actual_bond.space())
		throw IncompatibleMapDomain();
#endif
	int n = actual_bond.space().dim(), m = space().dim();
	coords = new double[2*m];
	map.apply(actual_bond.coords, coords);
	map.apply(actual_bond.coords + n, coords + m);
}

inline
ActualBond::~ActualBond(void)
{
	delete[] coords;
}

inline ActualGeomObj *
ActualBond::image(const Map &map) const
{
	ActualBond *mapped = new ActualBond(map, *this);
	return mapped;
}

class Bond
	: public GeomObj
{
public:
	Bond(const Space &space_);
	Bond(const Space &space_, std::istream &is);
	Bond(const Bond &bond);
	Bond(const Map &map, const Bond &bond);
	~Bond(void);

	Color color(void) const;
	Color &color(void);

	double beginning(int index) const;
	double &beginning(int index);
	double end(int index) const;
	double &end(int index);
	double length(void) const;
	Point midpoint(void) const;
	Point interpolant(double fraction) const;

	static const std::string name;

	class RangeViolation
		: public std::exception { };

protected:
	const ActualBond *actual_bond(void) const;
	ActualBond *actual_bond(void);
	void make_actual(void);
};

inline
Bond::Bond(const Space &space_)
	: GeomObj(new ActualBond(space_))
{
}

inline
Bond::Bond(const Space &space_, std::istream &is)
	: GeomObj(new ActualBond(space_, is))
{
}

inline
Bond::Bond(const Bond &bond)
	: GeomObj(bond)
{
}

inline
Bond::Bond(const Map &map, const Bond &bond)
	: GeomObj(map, bond)
{
}

inline const ActualBond *
Bond::actual_bond(void) const
{
	return dynamic_cast<ActualBond *>(actual);
}

inline ActualBond *
Bond::actual_bond(void)
{
	return dynamic_cast<ActualBond *>(actual);
}

inline Color
Bond::color(void) const
{
	return actual_bond()->color;
}

inline Color &
Bond::color(void)
{
	make_actual();
	return actual_bond()->color;
}

inline double
Bond::beginning(int index) const
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= space().dim())
		throw RangeViolation();
#endif
	return actual_bond()->coords[index];
}

inline double &
Bond::beginning(int index)
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= space().dim())
		throw RangeViolation();
#endif
	make_actual();
	return actual_bond()->coords[index];
}

inline double
Bond::end(int index) const
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= space().dim())
		throw RangeViolation();
#endif
	return actual_bond()->coords[space().dim() + index];
}

inline double &
Bond::end(int index)
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= space().dim())
		throw RangeViolation();
#endif
	make_actual();
	return actual_bond()->coords[space().dim() + index];
}

#endif
