#ifdef __GNUC__
#pragma implementation
#endif
#include <iostream>
#include <CoordsArray.h>
#include <Prims.h>
#include <Polygon.h>

Polygon::~Polygon(void)
{
}

void
ActualPolygon::draw(Prims &prims) const
{
//	prims.edge_color(color);
	CoordsArray coords_array(space().dim(), n_points, coords);
	prims.polygon(coords_array, color);
}

void
ActualPolygon::print(std::ostream &os) const
{
	int i, j, lim = space().dim() - 1;
	os << Polygon::name << " " << n_points << " " << color << "\n";
	double *coord = coords;
	for (j = 0; j < n_points; ++j) {
		for (i = 0; i < lim; ++i)
			os << *coord++ << " ";
		os << *coord++ << "\n";
	}
}

const std::string Polygon::name = "#Polygon";

void
Polygon::make_actual(void)
{
	if (duplicate()) {
		GeomObj::make_actual();
		actual = new ActualPolygon(*actual_polygon());
	}
}
