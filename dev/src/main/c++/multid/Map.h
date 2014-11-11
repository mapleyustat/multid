#ifndef _Map_h
#define _Map_h
#ifdef __GNUC__
#pragma interface
#endif

#include <exception>

class Space;
class GeomObj;
class Attributes;
class Point;

class Map
{
public:
	Map(const Space &domain_, const Space &codomain_);
	virtual ~Map(void);

	const Space &domain(void) const;
	const Space &codomain(void) const;

	virtual void apply(const double *in, double *out) const = 0;
	virtual void apply_inverse(const double *in, double *out) const;
	virtual void apply_derivative(const Point &origin, const double *in,
			double *out) const;
	virtual const Attributes *image_attributes(const GeomObj &geom_obj)
			const;

	class NotInvertible
		: public std::exception { };

private:
	const Space &dom;
	const Space &codom;
};

inline
Map::Map(const Space &domain_, const Space &codomain_)
	: dom(domain_),
	  codom(codomain_)
{
}

inline
Map::~Map(void)
{
}

inline const Space &
Map::domain(void) const
{
	return dom;
}

inline const Space &
Map::codomain(void) const
{
	return codom;
}

#endif
