#include <cmath>
#include "polyroot.h"

/*
*	quadratic_roots() solves a*x^2 + b*x + c = 0.
*
*	If:
*
*	(a) there are no real roots, the return value is QUAD_NO_REAL_ROOTS,
*	    x[0] is the (common) real part of the two roots,
*	    and x[1] is the imaginary part of the root that
*	    has positive imaginary part;
*	(b) there is one real root, the return value is QUAD_ONE_REAL_ROOT,
*	    and x[0] = x[1] is the root;
*	(c) there are two real roots, the return value is QUAD_TWO_REAL_ROOTS,
*	    and x[0] < x[1] are the two roots.
*/

int
quadratic_roots(double a, double b, double c, double x[2])
{
	double disc, q;

	disc = b*b - 4*a*c;
	if (disc < 0.) {
		x[0] = -.5*b/a;
		x[1] = .5*std::sqrt(-disc)/fabs(a);
		return QUAD_NO_REAL_ROOTS;
	}
	else if (disc == 0.) {
		x[0] = x[1] = - .5*b/a;
		return QUAD_ONE_REAL_ROOT;
	}
	else {
		if (b >= 0.) {
			q = -.5*( b + std::sqrt(b*b - 4*a*c) );
			x[0] = q/a;
			x[1] = c/q;
		}
		else {
			q = -.5*( b - std::sqrt(b*b - 4*a*c) );
			x[0] = c/q;
			x[1] = q/a;
		}
		return QUAD_TWO_REAL_ROOTS;
	}
}


/*
*	cubic_roots() solves x^3 + a*x^2 + b*x + c = 0.
*
*	If:
*
*	(a) there is one simple real root, the return value is
*	    CUBIC_TWO_NONREAL_ROOTS, x[0] is the real root, x[1] is
*	    the (common) real part of the two nonreal roots, and x[2]
*	    is the imaginary part of the nonreal root that has positive
*	    imaginary part;
*	(b) there is one triple real root, the return value is
*	    CUBIC_ONE_REAL_ROOT, and x[0] = x[1] = x[2] is the root;
*	(c) there is one double real root and a one simple real root,
*	    the return value is CUBIC_TWO_REAL_ROOTS, and x[0] <= x[1]
*	    <= x[2] is the root;
*	(d) there are three real roots, the return value is
*	    CUBIC_THREE_REAL_ROOTS, and x[0] < x[1] < x[2] are the three
*	    roots.
*/

#define M_SQRT3_2	.86602540378443864676
#define M_2PI_3		2.0943951023931954923
#define M_4PI_3		4.1887902047863909846

#define polish(s)	(t=s,t - (((t + a)*t + b)*t + c)/((3.*t + 2.*a)*t + b))

int
cubic_roots(double a, double b, double c, double x[3])
{
	double asqr, q, r, disc, t, t1, t2, t3, t4;

	asqr = a*a;
	q = (3.*b - asqr)/9.;
	r = (a*(9.*b - 2.*asqr) - 27.*c)/54.;
	disc = q*q*q + r*r;
	if (disc > 0.) {
		if (r >= 0.)
			t1 = std::pow(std::sqrt(disc) + r, 1./3.);	// S
		else
			t1 = - std::pow(std::sqrt(disc) - r, 1./3.);	// T
		t2 = q/t1;
		t3 = t1 - t2;						// S+T
		t4 = a/3.;
		x[0] = polish(t3 - t4);
		x[1] = -.5*t3 - t4;
		x[2] = M_SQRT3_2*(t1 + t2);
		return CUBIC_TWO_NONREAL_ROOTS;
	}
	else if (disc == 0.) {
		if (r > 0.) {
			t1 = std::pow(r, 1./3.);
			t4 = a/3.;
			x[0] = x[1] = -t1 - t4;
			x[2] = polish(2.*t1 - t4);
			return CUBIC_TWO_REAL_ROOTS;
		}
		else if (r == 0.) {
			x[0] = x[1] = x[2] = -a/3.;
			return CUBIC_ONE_REAL_ROOT;
		}
		else {
			t1 = std::pow(-r, 1./3.);
			t4 = a/3.;
			x[0] = polish(-2.*t1 - t4);
			x[1] = x[2] = t1 - t4;
			return CUBIC_TWO_REAL_ROOTS;
		}
	}
	else {
		t1 = std::atan2(std::sqrt(-disc), r)/3.;
		t2 = 2.*std::sqrt(-q);
		t4 = a/3.;
		x[0] = polish(t2*cos(t1+M_2PI_3) - t4);
		x[1] = polish(t2*cos(t1+M_4PI_3) - t4);
		x[2] = polish(t2*cos(t1) - t4);
		return CUBIC_THREE_REAL_ROOTS;
	}
}
