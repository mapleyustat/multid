#ifdef __GNUC__
#pragma implementation
#endif
#include <iostream>
#include <mathutil.h>
#include <CoordsArray.h>
#include <Prims.h>
#include <Bond.h>

ActualBond::ActualBond(const Space &space_, std::istream &is)
	: ActualGeomObj(space_),
	  color(Color::FOREGROUND),
	  coords(0)
{
	Color color_;
	is >> color_;
	if (is)
		color = color_;
	coords = new double[2*space().dim()];
	double *coord = coords;
	for (int i = 0; i < 2*space().dim(); ++i)
		is >> *coord++;
}

ActualBond::ActualBond(const ActualBond &actual_bond)
	: ActualGeomObj(actual_bond.space()),
	  color(actual_bond.color),
	  coords(0)
{
	int size = 2*space().dim();
	coords = new double[size];
	for (int i = 0; i < size; ++i)
		coords[i] = actual_bond.coords[i];
}

void
ActualBond::draw(Prims &prims) const
{
//	prims.line_color(color);
	CoordsArray coords_array(space().dim(), 2, coords);
	prims.polyline(coords_array);
}

void
ActualBond::print(std::ostream &os) const
{
	os << Bond::name << " " << color << "\n";
	int i, lim = 2*space().dim() - 1;
	double *coord = coords;
	for (i = 0; i < lim; ++i)
		os << *coord++ << " ";
	os << *coord << "\n";
}

const std::string Bond::name = "#Bond";

Bond::~Bond(void)
{
}

double
Bond::length(void) const
{
	double dist = 0.;
	int dim = space().dim();
	double *coords = actual_bond()->coords;
	for (int i = 0; i < dim; ++i)
		dist += sqr(coords[dim + i] - coords[i]);
	return static_cast<double>(sqrt(dist));
}

Point
Bond::midpoint(void) const
{
	Point middle(space());
	int dim = space().dim();
	double *coords = actual_bond()->coords;
	for (int i = 0; i < dim; ++i)
		middle[i] = .5f*(coords[i] + coords[dim + i]);
	return middle;
}

Point
Bond::interpolant(double fraction) const
{
	Point interp(space());
	int dim = space().dim();
	double *coords = actual_bond()->coords;
	for (int i = 0; i < dim; ++i)
		interp[i] = (1.f-fraction)*coords[i] + fraction*coords[dim + i];
	return interp;
}

void
Bond::make_actual(void)
{
	if (duplicate()) {
		GeomObj::make_actual();
		actual = new ActualBond(*actual_bond());
	}
}
