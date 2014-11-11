#ifndef _mathutil_h
#define _mathutil_h

#include <cmath>
#include <algorithm>

using std::abs;
using std::max;
using std::min;

inline double
sqr(double arg)
{
	return arg*arg;
}

extern const double BIG;
extern const double EPSILON;
extern const double SMALL;

#endif /* _mathutil_h */
