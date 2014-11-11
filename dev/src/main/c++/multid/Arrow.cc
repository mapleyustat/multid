#ifdef __GNUC__
#pragma implementation
#endif
#include <iostream>
#include <CoordsArray.h>
#include <Prims.h>
#include <Arrow.h>

const double sqrt3over10 = 0.17320508075688772935;

ActualArrow::ActualArrow(const Space &space_, std::istream &is)
	: ActualGeomObj(space_),
	  origin(space_),
	  color(Color::FOREGROUND),
	  coords(0)
{
	Color color_;
	is >> color_;
	if (is)
		color = color_;
	std::string buf;
	is >> buf; // Point::name
	Point org(space_, is);
	origin = org;
	coords = new double[space().dim()];
	double *coord = coords;
	for (int i = 0; i < space().dim(); ++i)
		is >> *coord++;
}

void
ActualArrow::draw(Prims &prims) const
{
//	prims.line_color(color);
	if (space().dim() == 2) {
		double c[10];

		c[0] = origin[0];
		c[1] = origin[1];
		c[2] = c[0] + coords[0];
		c[3] = c[1] + coords[1];
		c[4] = c[2] - sqrt3over10*coords[0] +        0.1f*coords[1];
		c[5] = c[3] -        0.1f*coords[0] - sqrt3over10*coords[1];
		c[6] = c[2] - sqrt3over10*coords[0] -        0.1f*coords[1];
		c[7] = c[3] +        0.1f*coords[0] - sqrt3over10*coords[1];
		c[8] = c[2];
		c[9] = c[3];

		CoordsArray coords_array(2, 5, c);
		prims.polyline(coords_array);
	}
	else if (space().dim() == 3) {
		double c[15];

		c[0] = origin[0];
		c[1] = origin[1];
		c[2] = origin[2];
		c[3] = c[0] + coords[0];
		c[4] = c[1] + coords[1];
		c[5] = c[2] + coords[2];
		c[6] = c[3]  - sqrt3over10*coords[0] +        0.1f*coords[1];
		c[7] = c[4]  -        0.1f*coords[0] - sqrt3over10*coords[1];
		c[8] = c[5]  - 0.1f*coords[2];
		c[9] = c[3]  - sqrt3over10*coords[0] -        0.1f*coords[1];
		c[10] = c[4] +        0.1f*coords[0] - sqrt3over10*coords[1];
		c[11] = c[5] - 0.1f*coords[2];
		c[12] = c[3];
		c[13] = c[4];
		c[14] = c[5];

		CoordsArray coords_array(3, 5, c);
		prims.polyline(coords_array);
	}
	else
		throw InappropriateDimension();
}

void
ActualArrow::print(std::ostream &os) const
{
	os << Arrow::name << " " << color << "\n";
	os << origin;
	int i, lim = space().dim() - 1;
	double *coord = coords;
	for (i = 0; i < lim; ++i)
		os << *coord++ << " ";
	os << *coord << "\n";
}

const std::string Arrow::name = "#Arrow";

Arrow::Arrow(const Space &space_, std::istream &is)
	: GeomObj(new ActualArrow(space_, is))
{
}

Arrow::~Arrow(void)
{
}

void
Arrow::make_actual(void)
{
	if (duplicate()) {
		GeomObj::make_actual();
		actual = new ActualArrow(*actual_arrow());
	}
}
