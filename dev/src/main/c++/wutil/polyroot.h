#ifndef _polyroot_h
#define _polyroot_h

#define QUAD_TWO_REAL_ROOTS	2
#define QUAD_ONE_REAL_ROOT	1
#define QUAD_NO_REAL_ROOTS	0

int
quadratic_roots(double a, double b, double c, double x[2]);

#define CUBIC_THREE_REAL_ROOTS	3
#define CUBIC_TWO_REAL_ROOTS	2
#define CUBIC_ONE_REAL_ROOT	1
#define CUBIC_TWO_NONREAL_ROOTS	0

int
cubic_roots(double a, double b, double c, double x[3]);

#endif /* _polyroot_h */
