#ifdef __GNUC__
#pragma implementation
#endif
#include <iostream>
#include <CoordsArray.h>
#include <Prims.h>
#include <Polyline.h>

void
ActualPolyline::draw(Prims &prims) const
{
//	prims.line_color(color);
	CoordsArray coords_array(space().dim(), n_points, coords);
	prims.polyline(coords_array);
}

void
ActualPolyline::print(std::ostream &os) const
{
	os << Polyline::name << " " << n_points << " " << color << "\n";
	double *coord = coords;
	int lim = space().dim() - 1;
	for (int j = 0; j < n_points; ++j) {
		for (int i = 0; i < lim; ++i)
			os << *coord++ << " ";
		os << *coord++ << "\n";
	}
}

const std::string Polyline::name = "#Polyline";

Polyline::Polyline(const Space &space_, std::istream &is)
	: GeomObj(new ActualPolyline(space_, is))
{
}

Polyline::~Polyline(void)
{
}

void
Polyline::make_actual(void)
{
	if (duplicate()) {
		GeomObj::make_actual();
		actual = new ActualPolyline(*actual_polyline());
	}
}
