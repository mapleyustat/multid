#ifdef __GNUC__
#pragma implementation
#endif
#include <iostream>
#include <CoordsArray.h>
#include <Prims.h>
#include <Point.h>

ActualPoint::ActualPoint(const Space &space_, std::istream &is)
	: ActualGeomObj(space_),
	  color(Color::FOREGROUND),
	  coords(0)
{
	Color color_;
	is >> color_;
	if (is)
		color = color_;
	coords = new double[space().dim()];
	double *coord = coords;
	for (int i = 0; i < space().dim(); ++i)
		is >> *coord++;
}

ActualPoint::ActualPoint(const ActualPoint &actual_point)
	: ActualGeomObj(actual_point.space()),
	  color(actual_point.color),
	  coords(0)
{
	int size = space().dim();
	coords = new double[size];
	for (int i = 0; i < size; ++i)
		coords[i] = actual_point.coords[i];
}

void
ActualPoint::draw(Prims &prims) const
{
//	prims.marker_color(color);
	CoordsArray coords_array(space().dim(), 1, coords);
	prims.multimarker(coords_array);
}

void
ActualPoint::print(std::ostream &os) const
{
	os << Point::name << " " << color << "\n";
	int lim = space().dim() - 1;
	double *coord = coords;
	for (int i = 0; i < lim; ++i)
		os << *coord++ << " ";
	os << *coord << "\n";
}

const std::string Point::name = "#Point";

Point::~Point(void)
{
}

double
Point::operator[](int index) const
{
#ifdef ERROR_CHECKING
	if (index < 0 || index >= space().dim())
		throw RangeViolation();
#endif
	return actual_point()->coords[index];
}

void
Point::make_actual(void)
{
	if (duplicate()) {
		GeomObj::make_actual();
		actual = new ActualPoint(*actual_point());
	}
}
