#ifdef __GNUC__
#pragma implementation
#endif
#include <iostream>
#include <CoordsArray.h>
#include <Prims.h>
#include <MultiPoint.h>

ActualMultiPoint::ActualMultiPoint(const Space &space_, std::istream &is)
	: ActualGeomObj(space_),
	  color(Color::FOREGROUND),
	  n_points(1),
	  coords(0)
{
	int n_points_;
	Color color_;
	is >> n_points_ >> color_;
	if (is) {
		n_points = n_points_;
		color = color_;
	}
	coords = new double[n_points*space().dim()];
	double *coord = coords;
	for (int j = 0; j < n_points; ++j)
		for (int i = 0; i < space().dim(); ++i)
			is >> *coord++;
}

ActualMultiPoint::ActualMultiPoint(const ActualMultiPoint &actual_multi_point)
	: ActualGeomObj(actual_multi_point.space()),
	  color(actual_multi_point.color),
	  n_points(actual_multi_point.n_points),
	  coords(0)
{
	int size = n_points*space().dim();
	coords = new double[size];
	for (int i = 0; i < size; ++i)
		coords[i] = actual_multi_point.coords[i];
}

void
ActualMultiPoint::draw(Prims &prims) const
{
//	prims.marker_color(color);
	CoordsArray coords_array(space().dim(), n_points, coords);
	prims.multimarker(coords_array);
}

void
ActualMultiPoint::print(std::ostream &os) const
{
	os << MultiPoint::name << " " << n_points << " " << color << "\n";
	double *coord = coords;
	int lim = space().dim() - 1;
	for (int j = 0; j < n_points; ++j) {
		for (int i = 0; i < lim; ++i)
			os << *coord++ << " ";
		os << *coord++ << "\n";
	}
}

const std::string MultiPoint::name = "#MultiPoint";

MultiPoint::~MultiPoint(void)
{
}

void
MultiPoint::make_actual(void)
{
	if (duplicate()) {
		GeomObj::make_actual();
		actual = new ActualMultiPoint(*actual_multi_point());
	}
}
