#ifdef __GNUC__
#pragma implementation
#endif
#include <CompositeMap.h>
#include <Point.h>

CompositeMap::CompositeMap(const Map &map1_, const Map &map2_)
	: Map(map1_.domain(), map2_.codomain()),
	  map1(map1_),
	  map2(map2_),
	  middle(new double[map1_.codomain().dim()])
{
}

CompositeMap::~CompositeMap(void)
{
	delete[] middle;
}

void
CompositeMap::apply(const double *in, double *out) const
{
	map1.apply(in, middle);
	map2.apply(middle, out);
}

void
CompositeMap::apply_inverse(const double *in, double *out) const
{
	map2.apply_inverse(in, middle);
	map1.apply_inverse(middle, out);
}

void
CompositeMap::apply_derivative(const Point &origin, const double *in,
		double *out) const
{
	map1.apply_derivative(origin, in, middle);
	Point mapped_origin(map1, origin);
	map2.apply_derivative(mapped_origin, middle, out);
}

// TODO:  fix this!
const Attributes *
CompositeMap::image_attributes(const GeomObj &geom_obj) const
{
	return map1.image_attributes(geom_obj);
}
