#ifdef __GNUC__
#pragma implementation
#endif
#include "Space.h"
#include "Proj3dMap.h"

Proj3dMap::Proj3dMap(const Space &domain_, const Space &codomain_,
		int x_comp__, int y_comp__, int z_comp__)
	: Map(domain_, codomain_),
	  x_comp_(x_comp__),
	  y_comp_(y_comp__),
	  z_comp_(z_comp__)
{
}

Proj3dMap::~Proj3dMap(void)
{
}

void
Proj3dMap::apply(const double *in, double *out) const
{
	out[0] = in[x_comp()];
	out[1] = in[y_comp()];
	out[2] = in[z_comp()];
}

void
Proj3dMap::apply_inverse(const double *in, double *out) const
{
	for (int i = 0; i < codomain().dim(); ++i)
		out[i] = 0.;
	out[x_comp()] = in[0];
	out[y_comp()] = in[1];
	out[z_comp()] = in[2];
}
