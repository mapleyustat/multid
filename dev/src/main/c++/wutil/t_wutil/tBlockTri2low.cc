#include <iostream>
#include <cmath>
#include "BlockTri2.h"

#ifndef M_PI
#define M_PI 3.141592653
#endif

int
main()
{
	const int n_eqn = 20;
	BlockTriMatrix2 M(n_eqn);
	BlockTriVector2 x(n_eqn), y(n_eqn), y_before(n_eqn), z(n_eqn);

	Matrix2 LL, L, D;

	for (int i = 0; i < n_eqn; i++) {

		i++;

//#define ORIG
//#define TEST
#define ANOTHER_TEST
#ifdef ORIG
		LL(0,0) = i-1;
		LL(1,0) = -1;
		LL(0,1) = i+1;
		LL(1,1) = i;
		L(0,0) = i+1;
		L(1,0) = i;
		L(0,1) = i-1;
		L(1,1) = -i;
		//double scale = 3.;	// fails: ill conditioned?
		double scale = 6.;	// OK, but somewhat large errors
		D(0,0) = -.4*scale;
		D(1,0) = .04*scale;
		D(0,1) = .04*scale;
		D(1,1) = .4*scale;
#endif
#ifdef TEST
		LL(0,0) = i-1;
		LL(1,0) = -1;
		LL(0,1) = i+1;
		LL(1,1) = i;
		L(0,0) = 1./(i+2);
		L(1,0) = 1./(i+1);
		L(0,1) = 1./i;
		L(1,1) = -1./(i+1);
		D(0,0) = -10.;
		D(1,0) = 1.;
		D(0,1) = 1.;
		D(1,1) = 10.;
#endif
#ifdef ANOTHER_TEST
		LL(1,0) = 0.001;
		LL(0,1) = -0.001;
		LL(1,1) = 0.001;
		LL(0,0) = 0.001;
		L(0,0) = 1./(i+2);
		L(1,0) = 1./(i+1);
		L(0,1) = 1./i;
		L(1,1) = -1./(i+1);
		D(0,0) = -10.;
		D(1,0) = 1.;
		D(0,1) = 1.;
		D(1,1) = 10.;
#endif

		i--;

		M.lower_lower_diagonal()(i) = LL;
		M.lower_diagonal()(i) = L;
		M.diagonal()(i) = D;
		y(i)(0) = i;
		y(i)(1) = i+1;
	}

	y_before = y;
	std::cout << "M before:\n";
	std::cout << "lower_lower:\n" << M.lower_lower_diagonal();
	std::cout << "lower:\n" << M.lower_diagonal();
	std::cout << "diag:\n" << M.diagonal();
	std::cout << "y before:\n" << y_before;

	solve_lower(M, x, y);

	// Compute z = M*x, which should equal y.
	z(0) = M.diagonal()(0)*x(0);
	z(1) = M.lower_diagonal()(0)*x(0) + M.diagonal()(1)*x(1);
	for (int i = 2; i < n_eqn; i++)
		z(i) = M.lower_lower_diagonal()(i-2)*x(i-2)
			+ M.lower_diagonal()(i-1)*x(i-1)
			+ M.diagonal()(i)*x(i);

	std::cout << "M after:\n";
	std::cout << "lower_lower:\n" << M.lower_lower_diagonal();
	std::cout << "lower:\n" << M.lower_diagonal();
	std::cout << "diag:\n" << M.diagonal();
	std::cout << "y after:\n" << y;

	std::cout << "x:\n" << x;
	std::cout << "M*x:\n" << z;
	std::cout << "M*x - y_before:\n" << z - y_before;

	return 0;
}
