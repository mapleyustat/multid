#ifndef _CompositeMap_h
#define _CompositeMap_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Map.h>

class CompositeMap
	: public Map
{
public:
	CompositeMap(const Map &map1_, const Map &map2_);
	~CompositeMap(void);

	void apply(const double *in, double *out) const;
	void apply_inverse(const double *in, double *out) const;
	void apply_derivative(const Point &origin, const double *in,
			double *out) const;
	const Attributes *image_attributes(const GeomObj &geom_obj) const;

private:
	CompositeMap(const CompositeMap &); // Do not define.
	CompositeMap &operator=(const CompositeMap &); // Do not define.

	const Map &map1;
	const Map &map2;
	double *middle;
};

#endif
