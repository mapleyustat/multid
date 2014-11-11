#ifdef __GNUC__
#pragma implementation
#endif
#include <iostream>
#include <Map.h>
#include <Point.h>

void
Map::apply_inverse(const double * /* in */, double * /* out */) const
{
	throw Map::NotInvertible();
}

void
Map::apply_derivative(const Point &origin, const double *in, double *out) const
{
	int i;
	int m = domain().dim(), n = codomain().dim();
	Point end_in(origin);
	for (i = 0; i < m; ++i)
		end_in[i] += in[i];
	Point begin_out(*this, origin);
	Point end_out(*this, end_in);
	for (i = 0; i < n; ++i)
		out[i] = end_out[i] - begin_out[i];
}

const Attributes *
Map::image_attributes(const GeomObj &geom_obj) const
{
	return geom_obj.attributes();
}
