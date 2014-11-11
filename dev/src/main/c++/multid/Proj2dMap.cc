#ifdef __GNUC__
#pragma implementation
#endif
#include "Space.h"
#include "Proj2dMap.h"

Proj2dMap::Proj2dMap(const Space &domain_, const Space &codomain_,
		int x_comp__, int y_comp__)
	: Map(domain_, codomain_),
	  x_comp_(x_comp__),
	  y_comp_(y_comp__)
{
}

Proj2dMap::~Proj2dMap(void)
{
}

int
Proj2dMap::y_comp(void) const
{
	return y_comp_;
}

void
Proj2dMap::apply(const double *in, double *out) const
{
	out[0] = in[x_comp()];
	out[1] = in[y_comp()];
}

void
Proj2dMap::apply_inverse(const double *in, double *out) const
{
	for (int i = 0; i < codomain().dim(); ++i)
		out[i] = 0.;
	out[x_comp()] = in[0];
	out[y_comp()] = in[1];
}
