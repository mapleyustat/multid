#ifndef _Proj3dMap_h
#define _Proj3dMap_h
#ifdef __GNUC__
#pragma interface
#endif

#include <Map.h>

class Proj3dMap
	: public Map
{
public:
	Proj3dMap(const Space &domain_, const Space &codomain_,
			int x_comp__, int y_comp__, int z_comp__);
	~Proj3dMap(void);

	void apply(const double *in, double *out) const;
	void apply_inverse(const double *in, double *out) const;

	int &x_comp(void);
	int x_comp(void) const;
	int &y_comp(void);
	int y_comp(void) const;
	int &z_comp(void);
	int z_comp(void) const;

private:
	int x_comp_, y_comp_, z_comp_;
};

inline int &
Proj3dMap::x_comp(void)
{
	return x_comp_;
}

inline int
Proj3dMap::x_comp(void) const
{
	return x_comp_;
}

inline int &
Proj3dMap::y_comp(void)
{
	return y_comp_;
}

inline int
Proj3dMap::y_comp(void) const
{
	return y_comp_;
}

inline int &
Proj3dMap::z_comp(void)
{
	return z_comp_;
}

inline int
Proj3dMap::z_comp(void) const
{
	return z_comp_;
}

#endif /* _Proj3dMap_h */
