#ifndef _Proj2dMap_h
#define _Proj2dMap_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Map.h>

class Proj2dMap
	: public Map
{
public:
	Proj2dMap(const Space &domain_, const Space &codomain_,
			int x_comp__, int y_comp__);
	~Proj2dMap(void);

	void apply(const double *in, double *out) const;
	void apply_inverse(const double *in, double *out) const;

	int &x_comp(void);
	int x_comp(void) const;
	int &y_comp(void);
	int y_comp(void) const;

private:
	int x_comp_, y_comp_;
};

inline int &
Proj2dMap::x_comp(void)
{
	return x_comp_;
}

inline int
Proj2dMap::x_comp(void) const
{
	return x_comp_;
}

inline int &
Proj2dMap::y_comp(void)
{
	return y_comp_;
}

#endif /* _Proj2dMap_h */
